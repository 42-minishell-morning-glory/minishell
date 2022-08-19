#include "minishell.h"

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

int	echo(char **argv)
{
	int	i;
	int	print_i;
	int	opt;

	i = 0;
	opt = 0;
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
	return (1);
}

int	cd(char *path)
{
	static char	*old_path;
	char		*tmp;

	if (path[0] == '-' && path[1] == '\0')
	{
		if (!old_path)
			printf("cd: OLDPWD not set\n");
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
		if (chdir(path))
			perror(strerror(errno));
	}
	return (0);
}

void	pwd(void) // 뒤에 오는 argv들 모두 금이빨 빼 씹어먹음
{
	printf("%s\n", getcwd(NULL, 0));
}

int	export(t_info *info, char *key_value)
{
	int	i;

	i = 0;
	while (key_value[i] &&key_value[i] != '=')
	{
		if (ft_isdigit(key_value[i]))
			return (0);
		i++;
	}
	if (!key_value[i])
		return (0);
	add_list_env(info, key_value);
	return (0);
}

int	env(t_dlist *env)
{
	t_dlist	*temp;

	temp = env;
	while (env != NULL)
	{
		printf("%s\n", env->token);
		temp = temp->next;
	}
	return (0);
}

int	unset(char *key)
{
	if (ft_isdigit(key[0]))
		re
}

int	mini_exit()
{
	if ()
	printf("exit\n");
	exit(0);	
}

int	main(int argc, char **argv, char **envp)
{
	char	*buf;

	(void) argc;
	(void) argv;
	env(envp);
	// buf = getcwd(NULL, 0);
	// printf("Before path : %s\n", buf);
	// free(buf);
	// chdir("../");
	// for (int i = 1; i < argc; i++)
	// 	cd(argv[i]);
	pwd();
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
}

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
