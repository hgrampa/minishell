#include <stdio.h>

void ft_echo (char *str, int arg_n)
{
	printf("%s", str);
	if (arg_n)
		printf("\n");
}

int main(int ac, char **av)
{
	if (ac == 2)
	{
		ft_echo(av[1], 0);
	}
	return (0);
}