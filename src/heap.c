/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjabri <mjabri@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/30 02:32:08 by mjabri            #+#    #+#             */
/*   Updated: 2026/09/06 02:01:55 by mjabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "threadsmith.h"

static void	swap_nodes(t_hnode *heap)
{
	t_hnode	temp;

	temp = heap[0];
	heap[0] = heap[1];
	heap[1] = temp;
}

void	heap_push(t_dongle *dongle, int coder_id, long priority)
{
	if (dongle->queue_size == 0)
	{
		dongle->queue[0].coder_id = coder_id;
		dongle->queue[0].priority = priority;
		dongle->queue_size = 1;
	}
	else if (dongle->queue_size == 1)
	{
		dongle->queue[1].coder_id = coder_id;
		dongle->queue[1].priority = priority;
		dongle->queue_size = 2;
		if (dongle->queue[1].priority < dongle->queue[0].priority)
			swap_nodes(dongle->queue);
	}
}

void	heap_pop(t_dongle *dongle)
{
	if (dongle->queue_size == 1)
		dongle->queue_size = 0;
	else if (dongle->queue_size == 2)
	{
		swap_nodes(dongle->queue);
		dongle->queue_size = 1;
	}
}

long	get_priority(t_coder *coder)
{
	if (coder->data->args.scheduler == 1)
		return (coder->last_compile + coder->data->args.t_burnout);
	return (time_get());
}
