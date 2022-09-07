#include "../minishell.h"

extern int	g_exit_code;

void	first_redir(t_info *info)
{
	close(info->tmp_fd);
	unlink(".minishell_tmp");
	dup2(info->in_fd, STDIN_FILENO); // 추가 ls > e
	dup2(info->out_fd, STDOUT_FILENO);
	close(info->in_fd);
	close(info->out_fd);
	info->redir_out_fd = 0;
	info->redir_in_flag = 0;
	info->tmp_fd = 0;
}

void	flag_on_redirin(t_info *info, t_tree *myself, int *r_fd)
{
	if (*r_fd != -1)
	{
		dup2(*r_fd, STDIN_FILENO);
		close(*r_fd);
	}
	else
		info->err_flag = 1;
	info->redir_in_flag = 1;
}

int	redir_input(t_info *info, t_tree *myself)
{
	char	*file_name;
	int		r_fd;
	int		left;

	file_name = myself->dlist->token;
	while (*file_name == '<')
		file_name++;
	r_fd = open(file_name, O_RDONLY, 0644);
	if (r_fd == -1 && (myself->left_child->dlist->type == WORD || !myself->left_child))
		return (puterr_exit_code(file_name, 0, 0));
	if (!info->redir_in_flag)
		flag_on_redirin(info, myself, &r_fd);
	left = execute(info, myself->left_child);
	if (left)
	{
		if (info->redir_cnt == 1)
			first_redir(info);
		return (left);
	}
	if (r_fd == -1)
		return (puterr_exit_code(file_name, 0, REPLACE_ONE));
	return (0);
}

void	flag_on_redirout(t_info *info, t_tree *myself, int *r_fd)
{
	info->tmp_fd = open(".minishell_tmp", O_CREAT | O_TRUNC | O_RDWR, 0644);
	dup2(info->tmp_fd, STDOUT_FILENO);
	close(info->tmp_fd);
	info->redir_out_fd = dup(*r_fd);
}

int	redir_output(t_info *info, t_tree *myself)
{
	char	*file_name;
	int		r_fd;
	int		left;

	file_name = myself->dlist->token;
	while (*file_name == '>')
		file_name++;
	if (myself->dlist->token[1] == '>')
		r_fd = open(file_name, O_CREAT | O_APPEND | O_RDWR, 0644);
	else
		r_fd = open(file_name, O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (!info->redir_out_fd)
		flag_on_redirout(info, myself, &r_fd);
	close(r_fd);
	left = execute(info, myself->left_child);
	if (left)
	{
		if (info->redir_cnt == 1)
			first_redir(info);
		if (left != 1)
			unlink(file_name); // exit code가 명령어에서 실패해서 1인거랑 인풋에서 읽었을떄 실패해서 1인거 구분
		return (left);
	}
	return (0);
}

void	append_list(t_tree *myself, int flag)
{
	t_dlist	*tmp1;
	t_dlist	*tmp2;
	t_tree	*target;

	if (!myself->right_child)
		return ;
	tmp1 = myself->right_child->dlist;
	if (flag == VERTICAL)
	{
		target = myself->left_child->right_child;
		if (target == NULL)
		{
			myself->left_child->right_child = myself->right_child;
			myself->right_child = 0;
			return ;
		}
	}
	else
	{
		target = myself->left_child;
		if (target == NULL)
		{
			myself->left_child = myself->right_child;
			myself->right_child = 0;
			return ;
		}
	}
	tmp2 = target->dlist;
	while (tmp2->next)
		tmp2 = tmp2->next;
	tmp2->next = tmp1;
	tmp1->prev = tmp2;
	free(myself->right_child);
	myself->right_child = 0;
}

void	make_friends(t_info *info, t_tree *myself)
{
	if (myself->left_child && myself->left_child->dlist->type != WORD)
	{
		append_list(myself, VERTICAL);
		make_friends(info, myself->left_child);
	}
	else
		append_list(myself, HORIZONTAL);
}

void	manage_redirfile(t_info *info, t_tree *myself, int ret)
{
	char	*gnl;

	info->tmp_fd = open(".minishell_tmp", O_RDONLY | O_CREAT, 0644);
	gnl = get_next_line(info->tmp_fd);
	while (gnl)
	{
		write(info->redir_out_fd, gnl, ft_strlen(gnl));
		free(gnl);
		gnl = get_next_line(info->tmp_fd);
	}
	close(info->redir_out_fd);
	first_redir(info);
}

int	execute_redir(t_info *info, t_tree *myself)
{
	int	ret;

	info->redir_cnt++;
	if (info->redir_cnt == 1)
		make_friends(info, myself);
	if (myself->dlist->token[0] == '<' && myself->dlist->token[1] != '<')
		ret = redir_input(info, myself);
	else if (myself->dlist->token[0] == '>')
		ret = redir_output(info, myself);
	if (!ret && info->redir_cnt == 1)
		manage_redirfile(info, myself, ret);
	info->redir_cnt--;
	return (ret);
}
