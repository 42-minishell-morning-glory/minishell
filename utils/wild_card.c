#include "../minishell.h"

int	wildcard(t_dlist *curr, char *path, t_dlist *temp)
{
	
	
	// 여기에 들어오는 token은 무조건 *달고 들어옴
	// 경우의 수 2가지
	// 1. 디렉토리에 *가 있는 경우 => '재귀'
	// 2. 파일이름에 *가 있는 경우 => 현재 디렉토리에서만 쓰니까 재귀 돌 필요 없다
	// <실행방법>
	// 1. path 분석 first
	// => '/' 앞에 *가 오는가? vs 뒤에 오는가 
	// 주의할 점은 ./*/a.c 인 경우가 예외사항 => <./>  <./././> 같이 의미 없는 것은 지워버리는 방법으로 해결 안지우면 작동이 안되나요? 
	// => 작동은 되는데 *가 '/' 뒤에 오는지 앞에 오는지 편하게 확인하기 위해서 지우면 좋을 것 같아요 넵
	// 2. 
	// ex) ././././*/hello.c    */hello.c   */   *.c
	무조건 별 앞에서 끊고
	별앞에 아무것도 없으면 ./
	이러면 되지 않나요?


	=>	*/hello.c
	open(".")
	pre = "./"
	post = "*/hello.c"
	dir_entry = readdir(dir_info);
	while (dir_entry)
		if "*/" in post:
			if dir_entry->d_name == directory:
				wildcard(curr, pre+dir_entry->d_name)
		else:
			if (ft_*판단)
				add_list(info, dir_entry->d_name)
		dir_entry = readdir(dir_info);
	
		
/* ************************************************************************** */
<해야할 것>
1. *.c
2. */hello
=> */*, */*/* 같은 것 못 씀 - 이해하셨나요 지니팍님  왜 못 써요? 원래 안돼요? 아하 이해했습니다

/* ************************************************************************** */

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


	path = a
	path = a/b
	path = a/b/c/

	paht2 = a/b/c/
	

	(a/b/c/   */*.c)
	a/b/c/dir/   *.c
	*/*/*/*.c
	a1/b1/c1/
	a2/b2/c2/
	a3/b3/c3/
	opendir(a);
	wildcard(b/c)


	dir2/*.c
	dir3/*.c

	*/*/*/*/
	/dir/*/*.c
	/dir/dir/*/dir/*.
	/abc.*
	abc/*
	마지막 / 까지
	*.c
	* 이거는 문자 그대로
	*/
	/*
	1. 마지막/에서 open
	2. *만나면 전 /까지 open
	3. 패스가 */로 들어왔을 때 while 돌면서 디렉토리면 wildcard()
	*/

	dir_info = opendir(""); 
	// cd opendir
	// libft/*/*.c
	// 재귀 함수 확인 
	// path = "libft/*.c" 
	// path에 directory가 있으면 cd 후 재귀 ex) opendir libft + wildcard("*.c");
	// 
	// 
}