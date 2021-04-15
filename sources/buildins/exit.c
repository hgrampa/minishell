#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void ft_exit()
{
	//free all fd
	//all child process go to fd=1
	//SIGCHLD to parent process
	exit(1);
}

int main()
{
	ft_exit();
	return (0);
}