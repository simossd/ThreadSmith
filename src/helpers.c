/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjabri <mjabri@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 23:49:43 by mjabri            #+#    #+#             */
/*   Updated: 2026/09/06 02:02:22 by mjabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "threadsmith.h"

int	c_atoit(char *str)
{
	int		i;
	long	sum;

	i = 0;
	sum = 0;
	if (!str || str[0] == '-' || str[0] == '\0')
		return (-1);
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			sum = sum * 10 + (str[i++] - '0');
			if (sum > 2147483647)
				return (-1);
		}
		else
			return (-1);
	}
	return ((int)sum);
}

int	checker(char *str)
{
	if (!str)
		return (-1);
	if (strcmp(str, "edf") == 0)
		return (1);
	if (strcmp(str, "fifo") == 0)
		return (2);
	return (-1);
}
