#include "../minishell.h"

extern int	g_exit_code;

void	first_redir(t_info *info)
{
	close(info->tmp_fd);
	dup2(info->in_fd, STDIN_FILENO);
	dup2(info->out_fd, STDOUT_FILENO);
	close(info->in_fd);
	close(info->out_fd);
	info->redir_out_flag = 0;
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
	r_fd = open(file_name, O_RDONLY);
	if (r_fd == -1 && (!myself->left_child || myself->left_child->dlist->type == WORD))
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
	if (!info->redir_out_flag && ++info->redir_out_flag)
		dup2(r_fd, STDOUT_FILENO);
	close(r_fd);
	left = execute(info, myself->left_child);
	if (left)
	{
		if (info->redir_cnt == 1)
			first_redir(info);
		if (left != 1)
			unlink(file_name);
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

int	execute_redir(t_info *info, t_tree *myself)
{
	int	ret;

	info->redir_cnt++;
	if (info->redir_cnt == 1)
	{
		info->in_fd = dup(STDIN_FILENO);
		info->out_fd = dup(STDOUT_FILENO);
		make_friends(info, myself);
	}
	if (myself->dlist->token[0] == '<' && myself->dlist->token[1] != '<')
		ret = redir_input(info, myself);
	else if (myself->dlist->token[0] == '>')
		ret = redir_output(info, myself);
	if (!ret && info->redir_cnt == 1)
		first_redir(info);
	info->redir_cnt--;
	return (ret);
}
