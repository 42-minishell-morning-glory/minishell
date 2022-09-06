#include "../minishell.h"

char	*get_home(t_info *info) // HOME을 찾기. HOME을 떄 cd하면  이거 뜸 
{
	t_dlist	*curr;
	char	*ret;
	
	curr = info->env;
	while (curr && ft_strncmp(curr->token, "HOME=", 5))
		curr = curr->next;
	if (!curr)
		return (NULL);
	ret = curr->token;
	ret += 5;
	return (ret);
}

int	add_export(t_info *info, char *old_path)
{
	char		*env;
	t_dlist		*env_list;
	t_dlist		*prev_lst;

	env = ft_strjoin("OLDPWD=", old_path);
	prev_lst = create_list();
	env_list = create_list();
	env_list->token = env;
	prev_lst->next = env_list;
	export(info, prev_lst);
	free(env);
	free(prev_lst);
	free(env_list);
	free(old_path);
}

int	cd(t_info *info, t_dlist *list) // 그냥 cd 했을때 처리
{
	static char	*old_path;
	char		*tmp;

	if (!list->next) // env에서 $HOME 찾아서 넣어주면 됨
	{
		if (!get_home(info))
			return (put_str_err(list, "HOME not set")); //[bash: cd: HOME not set]
		else
			chdir(get_home(info));
		return (0);
	}
	if (list->next->next)
		return (put_str_err(list, "too many arguments"));
	if (list->next->token[0] == '-' && list->next->token[1] == '\0')
	{
		if (!old_path)
			return (put_str_err(list, "OLDPWD not set"));
		else
		{
			tmp = getcwd(NULL, 0);
			chdir(old_path);
			old_path = tmp;
			tmp = getcwd(NULL, 0);
			printf("%s\n", tmp);
			free(tmp);
		}
	}
	else
	{
		old_path = getcwd(NULL, 0);
		if (chdir(list->next->token))
			puterr_exit_code("cd", 0, 0);
	}
	add_export(info, old_path);
	return (0);
}