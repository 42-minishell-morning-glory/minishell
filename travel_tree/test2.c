#include "../minishell.h"
// 자식에서 입력한 것 
// 부모에게 보내기 
// 예를 들어 int dup2(fd, stdout); 과 같이 사용하면 모든 출력이 fd로 향하게 된다.
int main()
{
	pid_t	pid;
	int		p_fd[2];
	int		status;

	if (pipe(p_fd) == -1)
		return (1);
	pid = fork();
	if (pid == 0) // 자식
	{
		dup2(p_fd[1], STDOUT_FILENO);
		close(p_fd[0]);
		execve("/bin/ls", (char *[2]){"/bin/ls", NULL}, 0);
		close(p_fd[1]);
	}
	else // 부모 
	{
		waitpid(pid, &status, 0);
		dup2(p_fd[0], STDIN_FILENO);
		close(p_fd[0]);
		close(p_fd[1]);
		execve("/bin/cat", (char *[3]){"/bin/cat", "-e", NULL}, 0);
	}
}
