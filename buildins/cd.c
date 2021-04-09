#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int ft_cd (char *str)
{
	//char cwd[100];
	int result;

	//printf("%s\n", getcwd(cwd, 100));
	result = chdir(str);
	//printf("%s\n", getcwd(cwd, 100));
	return(result);
}

int main(int ac, char **av)
{
	if (ac == 2)
		printf("%d\n", ft_cd(av[1]));
	return (0);
}