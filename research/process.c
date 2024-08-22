#include <stdio.h>
#include <unistd.h>

int main(void)
{

	printf("This is the starting process' pid (parent's) = %d\n", getpid()); // This pid will be the parent pid

	pid_t	pid;

	pid = fork(); // Here the processes split, each running a different execution flow

	// Fork returns the pid of the newly created child process
	printf("pid after fork() is %d.\nFirst, this will be the child's pid. Then it will be 0.\n", pid);

	if (pid < 0)
	{
		perror("fork failed");
		return (1);
	}
	// In the child process, fork()returns 0 to differenciate the child from the parent
	else if (pid == 0)
	{
		printf("This is the child process. PID = %d\n", getpid());
	}
	else
	{
		// Parent process
		printf("This is the parent process. PID = %d\n", getpid());
	}

	return (0);
}
