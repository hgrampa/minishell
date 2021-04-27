#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "environment.h"
#include "minishell.h"

void	print_export_list(t_list *collection)
{
	t_pair	*pair;
	t_list	*tmp;

	tmp = collection;
	while (tmp != NULL)
	{
		pair = tmp->data;
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(pair->key, 1);
		if (pair->value != NULL)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(pair->value, 1);
			ft_putstr_fd("\"", 1);
		}
		ft_putstr_fd("\n", 1);
		tmp = tmp->next;
	}
}

int	check_invalid_key(char *key)
{
	if (ft_isdigit(key[0]))
		return (1);
	while (*key)
	{
		if (!(ft_isalnum(*key) || *key == '_'))
			return (1);
		key++;
	}
	return (0);
}

int	check_for_plus(char *str)
{
	int	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i + 1] != '\0')
		i++;
	if (str[i] != '+')
		return (0);
	str[i] = '\0';
	return (1);
}
