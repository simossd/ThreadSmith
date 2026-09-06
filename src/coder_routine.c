/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjabri <mjabri@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/30 02:50:01 by mjabri            #+#    #+#             */
/*   Updated: 2026/09/06 02:01:18 by mjabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "threadsmith.h"

static void	interruptible_sleep(long ms, t_data *data)
{
	long	start;

	start = time_get();
	while (time_get() - start < ms && !sim_should_stop(data))
		usleep(500);
}

static int	do_one_cycle(t_coder *c)
{
	req_both_dongles(c);
	if (sim_should_stop(c->data))
		return (1);
	pthread_mutex_lock(&c->data->lock);
	c->last_compile = time_get();
	pthread_mutex_unlock(&c->data->lock);
	log_state(c->data, c->id, "is compiling");
	interruptible_sleep(c->data->args.t_compile, c->data);
	rel_both_dongles(c, c->data->args.dongle_cooldown);
	pthread_mutex_lock(&c->data->lock);
	c->compiles_done++;
	pthread_mutex_unlock(&c->data->lock);
	if (c->compiles_done >= c->data->args.n_compile_required)
		return (1);
	if (sim_should_stop(c->data))
		return (1);
	log_state(c->data, c->id, "is debugging");
	interruptible_sleep(c->data->args.t_debug, c->data);
	if (sim_should_stop(c->data))
		return (1);
	log_state(c->data, c->id, "is refactoring");
	interruptible_sleep(c->data->args.t_refactor, c->data);
	return (0);
}

void	*coder_routine(void *arg)
{
	t_coder	*c;

	c = (t_coder *)arg;
	while (!sim_should_stop(c->data)
		&& c->compiles_done < c->data->args.n_compile_required)
	{
		if (do_one_cycle(c))
			break ;
	}
	pthread_mutex_lock(&c->data->lock);
	c->done = 1;
	pthread_mutex_unlock(&c->data->lock);
	return (NULL);
}
