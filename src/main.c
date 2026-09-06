/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjabri <mjabri@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 06:01:39 by mjabri            #+#    #+#             */
/*   Updated: 2026/09/06 02:02:38 by mjabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "threadsmith.h"

static void	create_coders(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->args.n_coders)
	{
		pthread_create(&data->coders[i].coder_t, NULL, coder_routine,
			&data->coders[i]);
		i++;
	}
}

static void	join_coders(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->args.n_coders)
	{
		pthread_join(data->coders[i].coder_t, NULL);
		i++;
	}
}

int	main(int ac, char **av)
{
	int			*args;
	t_data		data;
	pthread_t	monitor;

	if (ac != 9)
		return (printf("Wrong number of arguments !"), 1);
	args = parsing(ac, av);
	if (!args)
		return (1);
	args_filling(args, &data.args);
	data.start_time = time_get();
	if (init_data(&data))
		return (1);
	create_coders(&data);
	pthread_create(&monitor, NULL, monitor_routine, &data);
	join_coders(&data);
	pthread_join(monitor, NULL);
	clean_data(&data);
	return (0);
}
