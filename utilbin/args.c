/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 15:28:04 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/11 15:41:34 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <unistd.h>
# include <stdio.h>

int main(int argc, char const *argv[], char const *envp[])
{
	printf("----------------------------------------\n");
	printf("argc = %d\n\n", argc);
	for (int i = 0; argv[i] != NULL; i++)
		printf("argv[%d] = \"%s\"\n", i, argv[i]);
	printf("----------------------------------------\n");
	// for (int i = 0; envp[i] != NULL; i++)
	// 	printf("envp[%d] = \"%s\"\n", i, envp[i]);
	return 0;
}
