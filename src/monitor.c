/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjabri <mjabri@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/30 02:58:11 by mjabri            #+#    #+#             */
/*   Updated: 2026/09/06 02:02:48 by mjabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "threadsmith.h"

int	sim_should_stop(t_data *data)
{
	int	stop;

	pthread_mutex_lock(&data->lock);
	stop = data->simulation_check;
	pthread_mutex_unlock(&data->lock);
	return (stop);
}

static void	wake_all_dongles(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->args.n_coders)
	{
		pthread_mutex_lock(&data->dongles[i].lock);
		pthread_cond_broadcast(&data->dongles[i].cond);
		pthread_mutex_unlock(&data->dongles[i].lock);
		i++;
	}
}

static int	all_coders_done(t_data *data)
{
	int	i;
	int	done;

	i = 0;
	while (i < data->args.n_coders)
	{
		pthread_mutex_lock(&data->lock);
		done = data->coders[i].done;
		pthread_mutex_unlock(&data->lock);
		if (!done)
			return (0);
		i++;
	}
	return (1);
}

static int	check_burnout(t_data *data)
{
	int		i;
	long	now;
	int		burned;

	i = 0;
	burned = -1;
	pthread_mutex_lock(&data->lock);
	now = time_get();
	while (i < data->args.n_coders && burned == -1)
	{
		if (!data->coders[i].done
			&& now - data->coders[i].last_compile > data->args.t_burnout)
			burned = i;
		i++;
	}
	if (burned != -1)
		data->simulation_check = 1;
	pthread_mutex_unlock(&data->lock);
	if (burned != -1)
	{
		log_state(data, data->coders[burned].id, "burned out");
		return (1);
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		if (check_burnout(data))
		{
			wake_all_dongles(data);
			return (NULL);
		}
		if (all_coders_done(data))
			return (NULL);
		usleep(1000);
	}
}
