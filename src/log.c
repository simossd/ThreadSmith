/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjabri <mjabri@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/31 05:25:41 by mjabri            #+#    #+#             */
/*   Updated: 2026/09/06 02:02:30 by mjabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "threadsmith.h"

void	log_state(t_data *data, int coder_id, char *msg)
{
	pthread_mutex_lock(&data->lock);
	printf("%ld %d %s\n", time_get() - data->start_time, coder_id, msg);
	pthread_mutex_unlock(&data->lock);
}
