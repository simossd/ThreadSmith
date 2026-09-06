/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjabri <mjabri@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/28 03:52:14 by mjabri            #+#    #+#             */
/*   Updated: 2026/09/06 02:02:14 by mjabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "threadsmith.h"

void	init_dongles(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->args.n_coders)
	{
		pthread_mutex_init(&data->dongles[i].lock, NULL);
		pthread_cond_init(&data->dongles[i].cond, NULL);
		data->dongles[i].is_used = 0;
		data->dongles[i].cool_down = 0;
		data->dongles[i].id = i;
		data->dongles[i].queue_size = 0;
		i++;
	}
}

void	init_coders(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->args.n_coders)
	{
		data->coders[i].id = i + 1;
		data->coders[i].compiles_done = 0;
		data->coders[i].last_compile = data->start_time;
		data->coders[i].done = 0;
		data->coders[i].data = data;
		data->coders[i].first_dongle = &data->dongles[i];
		data->coders[i].second_dongle
			= &data->dongles[(i + 1) % data->args.n_coders];
		i++;
	}
}

int	init_data(t_data *data)
{
	data->dongles = malloc(sizeof(t_dongle) * data->args.n_coders);
	if (!data->dongles)
		return (1);
	data->coders = malloc(sizeof(t_coder) * data->args.n_coders);
	if (!data->coders)
	{
		free(data->dongles);
		return (1);
	}
	pthread_mutex_init(&data->lock, NULL);
	data->simulation_check = 0;
	init_dongles(data);
	init_coders(data);
	return (0);
}

void	clean_data(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->args.n_coders)
	{
		pthread_mutex_destroy(&data->dongles[i].lock);
		pthread_cond_destroy(&data->dongles[i].cond);
		i++;
	}
	free(data->dongles);
	free(data->coders);
	pthread_mutex_destroy(&data->lock);
}
