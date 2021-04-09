#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

char *ft_pwd()
{
	char *result;

	result = (char *)malloc(100);
	result = getcwd(result, 100);
	return(result);
}

int main()
{
	printf("%s\n", ft_pwd());
	return (0);
}