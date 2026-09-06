/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threadsmith.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjabri <mjabri@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 23:49:55 by mjabri            #+#    #+#             */
/*   Updated: 2026/09/06 02:04:35 by mjabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREADSMITH_H
# define THREADSMITH_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data	t_data;

typedef struct s_args
{
	int	n_coders;
	int	t_burnout;
	int	t_compile;
	int	t_debug;
	int	t_refactor;
	int	n_compile_required;
	int	dongle_cooldown;
	int	scheduler;
}	t_args;

typedef struct s_hnode
{
	int		coder_id;
	long	priority;
}	t_hnode;

typedef struct s_dongle
{
	int				id;
	pthread_mutex_t	lock;
	pthread_cond_t	cond;
	int				is_used;
	long			cool_down;
	t_hnode			queue[2];
	int				queue_size;
}	t_dongle;

typedef struct s_coder
{
	pthread_t		coder_t;
	int				id;
	t_dongle		*first_dongle;
	t_dongle		*second_dongle;
	t_data			*data;
	int				compiles_done;
	long			last_compile;
	int				done;
}	t_coder;

struct s_data
{
	t_args			args;
	t_dongle		*dongles;
	t_coder			*coders;
	pthread_mutex_t	lock;
	long			start_time;
	int				simulation_check;
};

int		c_atoit(char *str);
int		checker(char *str);
int		*parsing(int ac, char **av);
void	args_filling(int *args, t_args *arguments);
int		init_data(t_data *data);
void	clean_data(t_data *data);
void	dongle_release(t_dongle *dongle, long cooldown);
int		donlge_requester(t_coder *coder, t_dongle *dongle);
void	req_both_dongles(t_coder *coder);
void	rel_both_dongles(t_coder *coder, long cooldown);
long	get_priority(t_coder *coder);
void	heap_push(t_dongle *dongle, int coder_id, long priority);
void	heap_pop(t_dongle *dongle);
void	*coder_routine(void *arg);
long	time_get(void);
void	*monitor_routine(void *arg);
int		sim_should_stop(t_data *data);
void	log_state(t_data *data, int coder_id, char *msg);

#endif