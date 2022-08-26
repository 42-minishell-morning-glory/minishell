#include "../minishell.h"

int	check_wildcard(t_dlist *curr, char quote, int i, int w_cnt)
{
	char	*tmp;

	tmp = curr->token;
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
			if (tmp[i + 1] == '*')
				return (put_syntaxerr_msg("*"));
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

int	filter_wildcard(char *next_path, char *d_name, int path_len, int name_len)
{
	int	i;

	i = 0;
	//printf("WHAT THE fuCK : %s,  %s\n", next_path, d_name);
	while (next_path[i] != '*')
	{
		if (next_path[i] != d_name[i])
			return (0);
		i++;
	}
	if (next_path[path_len - 1] == '/')
		path_len--;
	while (next_path[--path_len] != '*')
	{
		if (next_path[path_len] != d_name[--name_len])
			return (0);
	}
	return (1);
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
		if (next_path[0] == '.')
		{
			if (ft_strnstr(next_path, "*/", ft_strlen(next_path))
				&& dir_entry->d_name[0] == '.' && dir_entry->d_type == 4
				&& filter_wildcard(next_path, dir_entry->d_name, ft_strlen(next_path), ft_strlen(dir_entry->d_name)))
			{
				curr_path = ft_str_rep_wildcard(dir_entry->d_name, next_path);
				add_list(&tmp_info, curr_path);
			}
			else if (dir_entry->d_type == 8
				&& filter_wildcard(next_path, dir_entry->d_name, ft_strlen(next_path), ft_strlen(dir_entry->d_name)))
				add_list(&tmp_info, dir_entry->d_name);
		}
		else
		{
			if (dir_entry->d_name[0] != '.' && dir_entry->d_type == 4
				&& filter_wildcard(next_path, dir_entry->d_name, ft_strlen(next_path), ft_strlen(dir_entry->d_name)))
			{
				printf("HEY\n");
				curr_path = ft_str_rep_wildcard(dir_entry->d_name, next_path);
				add_list(&tmp_info, curr_path);
			}
			else if (dir_entry->d_name[0] != '.' && dir_entry->d_type == 8
				&& filter_wildcard(next_path, dir_entry->d_name, ft_strlen(next_path), ft_strlen(dir_entry->d_name)))
				add_list(&tmp_info, dir_entry->d_name);
		}
		dir_entry = readdir(dir_info);
	}
	free(next_path);
	return (tmp_info.dlist);
}

int	wildcard(t_dlist **now)
{
	char	*curr_path;
	char	*next_path;
	int		last_dir_idx;
	t_dlist	*new_list;

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
	new_list = change_to_word(curr_path, next_path); // 리스트 프리
	if (new_list && set_list(*now, new_list))
		*now = new_list;
	return (0);
}
