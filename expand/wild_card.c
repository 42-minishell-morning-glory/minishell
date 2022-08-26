#include "../minishell.h"

int	check_wildcard(t_dlist *curr, char quote, int i, int w_cnt)
{
	char	*tmp;

	tmp = curr->token;
	if (tmp[0] == '/')
		return (0);
	while (tmp[i])
	{
		if (tmp[i] == '\'' || tmp[i] == '\"')
		{
			quote = tmp[i++];
			while (tmp[i] != quote)
				i++;
		}
		else if (tmp[i] == '*')
		{
			w_cnt++;
			if (w_cnt >= 2)
				return (0);
		}
		i++;
	}
	if (!w_cnt)
		return (0);
	return (1);
}

int	find_dir(char *path)
{
	int	i;
	int	last_dir_idx;
	
	i = 0;
	last_dir_idx = 0;
	while (path[i] && path[i] != '*')
	{
		if (path[last_dir_idx + 1] == 0)
			break ;
		if (path[i] == '/')
			last_dir_idx = i;
		i++;
	}
	return (last_dir_idx);
}

int	filter_wildcard(char *next_path, char *d_name, int path_len, int name_len) // ab*c, abc
{
	int	i;

	i = 0;
	while (next_path[i] != '*')
	{
		if (next_path[i] != d_name[i])
			return (0);
		i++;
	}
	while (next_path[--path_len] != '*')
	{
		if (next_path[path_len] != d_name[--name_len])
			return (0);
	}
	return (1);
}

char	*ft_str_rep_wildcard(char *d_name, char *next_path)
{
	char	*tmp;
	int		i;

	i = asdasd();
	tmp = ft_strdup(&next_path[i]);
	ft_strjoin_free(d_name, tmp);
	
}


t_dlist *change_to_word(char *curr_path, char *next_path)
{
	DIR				*dir_info;
	struct dirent	*dir_entry;
	t_info			tmp_info;
	
	dir_info = opendir(curr_path);
	dir_entry = readdir(dir_info);
	free(curr_path);
	tmp_info.dlist = NULL;
	while (dir_entry)
	{
		if (ft_strnstr(next_path, "*/", 2))
		{
			if (dir_entry->d_type == 8)
			{
				// ft_str_rep_wildcard(dir_entry->d_name, next_path);
				curr_path = ft_strjoin(dir_entry->d_name, "/");
				curr_path = ft_strjoin_free(curr_path, next_path);
				add_list(&tmp_info, curr_path);
			}
		}
		else
			if (filter_wildcard(next_path, dir_entry->d_name, ft_strlen(next_path), ft_strlen(dir_entry->d_name)))
				add_list(&tmp_info, dir_entry->d_name);
		dir_entry = readdir(dir_info);
	}
	free(next_path);
	if (tmp_info.dlist)
		printList(&tmp_info);
	return (tmp_info.dlist);
}

int	set_list(t_dlist *curr, t_dlist *new_list)
{
	t_dlist	*temp;

	temp = new_list;
	temp->type = WORD;
	if (curr->prev)
	{
		temp->prev = curr->prev;
		curr->prev->next = temp;
	}
	while (temp->next)
	{
		temp = temp->next;
		temp->type = WORD;
	}
	if (curr->next)
	{
		temp->next = curr->next;
		curr->next->prev = temp;
	}
	return (1);
}

int	wildcard(t_dlist **now)
{
	char			*curr_path;
	char			*next_path;
	int				last_dir_idx;
	t_dlist			*new_list;

	if (!check_wildcard(*now, 0, 0, 0))
		return (0);
	last_dir_idx = find_dir((*now)->token);
	if (!last_dir_idx)
	{
		curr_path = ft_strdup("./");
		next_path = ft_strdup((*now)->token);
	}
	else
	{
		curr_path = ft_strndup((*now)->token, last_dir_idx + 1);
		next_path = ft_strdup(&(*now)->token[last_dir_idx + 1]);
	}
	printf("|%d|\n", last_dir_idx);
	printf("hey curr_path: |%s|\n",curr_path);
	printf("hey next_path: |%s|\n",next_path);
	new_list = change_to_word(curr_path, next_path);
	if (new_list && set_list(*now, new_list))
		*now = new_list;
	return (0);
}
