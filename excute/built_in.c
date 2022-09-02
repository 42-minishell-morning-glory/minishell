#include "../minishell.h"

int	is_echo_option(char *arg)
{
	int	i;

	if (arg[0] != '-')
		return (0);
	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	echo(t_dlist *list)
{
	int		i;
	int		print_i;
	int		opt;
	char	**argv;

	i = 0;
	opt = 0;
	argv = make_command(list->next);
	while (argv[i] && is_echo_option(argv[i]))
		i++;
	if (i > 0)
		opt = 1;
	print_i = i;
	while (argv[i])
	{
		if (i == print_i)
			printf("%s", argv[i]);
		else
			printf(" %s", argv[i]);
		i++;
	}
	if (!opt)
		printf("\n");
	free(argv);
	return (0);
}

char	*list2p(t_dlist *list)
{
	t_dlist	*tmp;
	char	*key;

	tmp = list;
	key = ft_strdup(tmp->token);
	tmp = tmp->next;
	while (tmp)
	{
		key = ft_strjoin(key, tmp->token);
		tmp = tmp->next;
	}
	return (key);
}

int	unset(t_info *info, t_dlist *list)
{
	t_dlist	*tmp;
	char	*key;

	tmp = info->env;
	key = list2p(list->next);
	if (ft_isdigit(key[0])
		&& printf("minishell: unset: '%s': not a valid identifier\n", key))
		return (0);
	if (key[0] == '-' && printf("usage: unset [name ...]\n"))
		return (0);
	while (tmp)
	{
		if (ft_strncmp(tmp->token, key, ft_strlen(key) + 1) == '=')
			break ;
		tmp = tmp->next;
	}
	if (!tmp)
		return (1);
	delete_node(&info->env, tmp);
	free(key);
	printf("외안되\n");
	env(info, 0);
	return (0);
}

int	env(t_info *info, int flag)
{
	t_dlist	*temp;

	printf("나는 환경변수\n");
	temp = info->env;
	while (temp != NULL)
	{
		if (flag == 1)
			printf("declare -x ");
		printf("%s\n", temp->token);
		temp = temp->next;
	}
	return (0);
}

// int	export(t_info *info, char *key_value)

int	env_check(t_info *info, t_dlist *env_list, char *key_value)
{
	char	*temp;
	int		i;

	i = ft_strlen(key_value);
	// while (env_list)
	// {
	// 	if (!ft_strncmp(key_value, env_list->token, i))
	// 	{
	// 		// temp = ft_strndup(env->token, i - 1);
	// 		unset(info, env_list);
	// 		// free(temp);
	// 	}
	// 	env_list = env_list->next;
	// }
	return (0);
}

int key_check(char *token)
{
	int i;
	
	i = 0;
	while (token[i] && token[i] != '=')
	{
		if (ft_isdigit(token[i])) //export 1=e
		{
			printf("minishell: export: `%s': not a valid identifier\n", token);
			return (1);
		}
		if (!token[i]) // export a 
			return (1);
		i++;
	}
	return (0);
}

int	export(t_info *info, t_dlist *list)
{
	int		i;
	t_dlist	*curr;
	t_dlist	*env_list;

	curr = list->next;
	printf("curr token :%s \n", curr->token);
	env_list = info->env;
	if (!curr)
	{
		env(info, 1);
		return (0);
	} //문제없음!

	while (curr)
	{
		if (1)
		{
			printf("hey : %s\n", curr->token);
			add_list_env(info, curr->token);
		}
		curr = curr->next;
	}
	env(info, 0);
	// && !env_check(info, env_list, curr->token)
	return (0);
}


int	cd(t_info *info, t_dlist *list)
{
	static char	*old_path;
	char		*tmp;
	char		*env;
	t_dlist		*env_list;
	t_dlist		*prev_lst;

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
			printf("%s\n", getcwd(NULL, 0));
		}
	}
	else
	{
		old_path = getcwd(NULL, 0);
		if (chdir(list->next->token))
			perror(strerror(errno));
	}
	env = ft_strjoin("OLDPWD=", old_path);
	prev_lst = create_list();
	env_list = create_list();
	env_list->token = env;
	prev_lst->next = env_list;
	export(info, prev_lst);
	free(env);
	return (0);
}

int	pwd(void) // 뒤에 오는 argv들 모두 금이빨 빼 씹어먹음
{
	printf("%s\n", getcwd(NULL, 0)); // 수정 필요 pwd > a 가능함
	return (0);
}

int	mini_exit(t_dlist *list)
{
	int	exit_code;

	if (list->next)
		exit_code = ft_atoi(list->next->token);
	else
		exit_code = 0;
	printf("exit\n");
	exit(exit_code);
}

int	built_in(t_info *info, t_tree *myself)
{
	char	*token;

	token = myself->dlist->token;
	if (!ft_strncmp(token, "echo", 5))
		return (echo(myself->dlist));
	else if (!ft_strncmp(token, "cd", 3))
		return (cd(info, myself->dlist));
	else if (!ft_strncmp(token, "unset", 6))
		return (unset(info, myself->dlist));
	else if (!ft_strncmp(token, "env", 4))
		return (env(info, 0));
	else if (!ft_strncmp(token, "pwd", 4))
		return (pwd());
	else if (!ft_strncmp(token, "export", 7))
		return (export(info, myself->dlist));
	else if (!ft_strncmp(token, "exit", 5))
		return (mini_exit(myself->dlist));
	return (-1);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	char	*buf;
// 	t_info	info;
// 	int	i;

// 	i = 0;
// 	ft_memset(&info, 0, sizeof(t_info));
// 	(void) argc;
// 	(void) argv;
// 	while (envp[i])
// 	{
// 		add_list_env(&info, envp[i]);
// 		i++;
// 	}
// 	export(&info, ft_strdup("a=1"));
// 	unset(&info, "a");
// 	env(info.env, 0);
	// unset(info.env, "abc");
	// buf = getcwd(NULL, 0);
	// printf("Before path : %s\n", buf);
	// free(buf);
	// chdir("../");
	// for (int i = 1; i < argc; i++)
	// 	cd(argv[i]);
	//pwd();
	// pwd = buf(현재 경로) + argv (..);
	// chdir(pwd);
	// buf = getcwd(NULL, 30);
	// printf("After path : %s\n", buf);
	// echo(argv + 1);
/*
getcwd의 특이한 점으로는 buf의 인자로 NULL을 넣게 되면, 
내부적으로 size만큼의 크기로 동적 할당을 받아 해당 공간의 주소를 반환하게 된다. 
만일 size 만큼의 크기로 동적 할당을 받아서 절대 경로를 기록하는 것이 불가능하다면, 
절대 경로를 기록할 수 있을 만큼의 크기로 동적 할당을 받게 된다. 
이 경우에는 동적 할당 받은 공간에 대해서 사용자가 직접 free를 호출해야 한다. 
만일 함수 수행에 문제가 있다면, NULL을 반환한다.
*/

/* 
	[cd 에러메세지]
	- cd 234 987 (cd 인자가 두 개 이상일때)
		minishell: cd: 234: No such file or directory
	- unset HOME 한 후 cd $HOME 했을 때
		"minishell: cd: HOME not set"
	- 올바르지 않은 폴더 경로일때
		"minishell: cd: 인자: No such file or directory"
*/

/* 
build-in func
- cd
- pwd
- env
- export
- unset
- echo
- exit
*/
