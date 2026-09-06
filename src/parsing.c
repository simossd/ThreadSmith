/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjabri <mjabri@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 05:47:22 by mjabri            #+#    #+#             */
/*   Updated: 2026/09/06 02:03:05 by mjabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "threadsmith.h"

int	*parsing(int ac, char **av)
{
	int	*args;
	int	i_args;
	int	args_len;
	int	algo_checks;

	i_args = 1;
	args_len = 0;
	args = malloc((sizeof(int) * 8));
	if (!args)
		return (NULL);
	while (i_args < (ac - 1))
	{
		args[args_len++] = c_atoit(av[i_args++]);
		if (args[args_len - 1] < 0)
			return (printf("Wrong arguments passed !"), free(args), NULL);
	}
	if (args[0] < 1)
		return (printf("nb_coders can't be less than 1"), free(args), NULL);
	algo_checks = checker(av[8]);
	if (algo_checks < 1)
		return (printf("You can use fifo or edf only !"), free(args), NULL);
	args[args_len] = algo_checks;
	return (args);
}

void	args_filling(int *args, t_args *argments)
{
	argments->n_coders = args[0];
	argments->t_burnout = args[1];
	argments->t_compile = args[2];
	argments->t_debug = args[3];
	argments->t_refactor = args[4];
	argments->n_compile_required = args[5];
	argments->dongle_cooldown = args[6];
	argments->scheduler = args[7];
	free(args);
}
