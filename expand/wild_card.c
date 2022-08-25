#include "../minishell.h"

int	check_wd(char *token)
{
	int i;
	int w_cnt;
	
	i = 0;
	w_cnt = 0;
	while (token[i])
	{
		if (token[0] = '/' || w_cnt >= 2)
			return (0);
		if (token[i] == '*')
			w_cnt++;
		i++;
	}
	return (1);
}

int	wildcard(t_dlist *curr, char *path, t_dlist *temp)
{	
	DIR				*dir_info;
	struct dirent	*dir_entry;
	char			*pre;
	char			*post;
	t_info			*tmp_info;
	int				i;

	if (!check_wd(curr->token))
		return ;
	i = 0;
	while (curr->token[i] != '*') // ./././././* or */
		i++;
	if (i == 0)
	{
		pre = ft_strdup("./");
		post = ft_strdup(curr->token);
	}
	else
	{
		pre = ft_strndup(curr->token, i);
		post = ft_strdup(&curr->token[i]);
	}
	dir_info = opendir(pre);
	dir_entry = readdir(dir_info);
	while (dir_entry)
	{
		if (ft_strstr(post, "*/"))
			wildcard(info, pre+dir_entry->d_name);
		else
			if (판단(*, hello.c))
				add_list(info, dir_entry->d_name);
		dir_entry = readdir(dir_info);
	}
	
	
	
	if (ft_strchr(curr->token + i, '/')) // d/hello         *.c     ././././*.c
	{
		dir_info = opendir(".");
		dir_entry = readdir(dir_info);
		tmp_path = ft_strndup(ft_strjoin(dir_entry->d_name, , );
	}
	else // *.c
	{
		dir_info = opendir(tmp_path);
		dir_entry = readdir(dir_info);
	}
	while (dir_entry->name)
	{
		dir_entry->d_name

		recursive_wildcard(curr, tmp_path, temp);
	}
	
/************************PYTHON********************************/
	// 옾=>	*/hello.c
	open(".")
	pre = "./"
	post = "*/hello.c"
	dir_entry = readdir(dir_info);
	while (dir_entry)
		if "*/" in post:
			if dir_entry->d_name == directory:
				wildcard(curr, pre+dir_entry->d_name)
		else:
			add_list(info, dir_entry->d_name)
		dir_entry = readdir(dir_info);
/**************************************************************/


	DIR				*dir_info;
	struct dirent	*dir_entry;
	char			*tmp_path;
	t_info			*tmp_info;


	dir_info = opendir("a/b/c");
	if (dir_info != NULL)
	{
		dir_entry = readdir(dir_info);
		while (dir_entry)
		{
			if (".c" in dir_entry->d_name)
			{
				printf("DIR : %s type : %hhu\n", dir_entry->d_name, dir_entry->d_type);
				add_list(curr, dir_entry->d_name); //curr을 받아야 함
			}
			dir_entry = readdir(dir_info);
		}
		closedir(dir_info);  
		return (1);
	}

}