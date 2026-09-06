/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjabri <mjabri@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/28 04:23:46 by mjabri            #+#    #+#             */
/*   Updated: 2026/09/06 02:01:39 by mjabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "threadsmith.h"

long	time_get(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

static void	wait_for_dongle(t_dongle *dongle, t_coder *coder)
{
	struct timespec	deadline;

	while (!sim_should_stop(coder->data) && (dongle->is_used
			|| time_get() < dongle->cool_down
			|| dongle->queue[0].coder_id != coder->id))
	{
		if (dongle->is_used || dongle->queue[0].coder_id != coder->id)
			pthread_cond_wait(&dongle->cond, &dongle->lock);
		else
		{
			deadline.tv_sec = dongle->cool_down / 1000;
			deadline.tv_nsec = (dongle->cool_down % 1000) * 1000000L;
			pthread_cond_timedwait(&dongle->cond, &dongle->lock, &deadline);
		}
	}
}

int	donlge_requester(t_coder *coder, t_dongle *dongle)
{
	long	priority;

	pthread_mutex_lock(&dongle->lock);
	priority = get_priority(coder);
	heap_push(dongle, coder->id, priority);
	wait_for_dongle(dongle, coder);
	if (sim_should_stop(coder->data))
	{
		pthread_mutex_unlock(&dongle->lock);
		return (0);
	}
	heap_pop(dongle);
	dongle->is_used = 1;
	pthread_mutex_unlock(&dongle->lock);
	return (1);
}

void	dongle_release(t_dongle *dongle, long cooldown)
{
	pthread_mutex_lock(&dongle->lock);
	dongle->is_used = 0;
	dongle->cool_down = time_get() + cooldown;
	pthread_cond_broadcast(&dongle->cond);
	pthread_mutex_unlock(&dongle->lock);
}
