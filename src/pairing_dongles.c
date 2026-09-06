/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pairing_dongles.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjabri <mjabri@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/29 05:36:11 by mjabri            #+#    #+#             */
/*   Updated: 2026/09/06 02:02:56 by mjabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "threadsmith.h"

void	req_both_dongles(t_coder *coder)
{
	t_dongle	*first;
	t_dongle	*second;

	if (coder->first_dongle->id < coder->second_dongle->id)
	{
		first = coder->first_dongle;
		second = coder->second_dongle;
	}
	else
	{
		first = coder->second_dongle;
		second = coder->first_dongle;
	}
	if (!donlge_requester(coder, first))
		return ;
	if (!donlge_requester(coder, second))
		return ;
	pthread_mutex_lock(&coder->data->lock);
	printf("%ld %d has taken a dongle\n", time_get()
		- coder->data->start_time, coder->id);
	printf("%ld %d has taken a dongle\n", time_get()
		- coder->data->start_time, coder->id);
	pthread_mutex_unlock(&coder->data->lock);
}

void	rel_both_dongles(t_coder *coder, long cooldown)
{
	dongle_release(coder->first_dongle, cooldown);
	dongle_release(coder->second_dongle, cooldown);
}
