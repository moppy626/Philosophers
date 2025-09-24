/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 14:03:42 by mmachida          #+#    #+#             */
/*   Updated: 2025/09/24 18:16:54 by mmachida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h> // pthread_t
#include "ft_lst.h"

#ifndef DEBUG
# define DEBUG 0
#endif
	
#define MONITOR_SLEEP 500

typedef struct s_data
{
	long			starttime;
	int				stoped;
	pthread_t		thread_monitor;
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_eat_time;
	int				specified_eat_time;
	t_list			*forks;
	pthread_mutex_t mutex_print;
}	t_data;

typedef struct s_philo
{
	int				id;
	int 			right_fork;
	int 			left_fork;
	long			lastmeal_time;
	int				num_of_meals;
	pthread_t		thread;
	pthread_mutex_t mutex_philo;
	t_data			*d;
}	t_philo;

typedef struct s_fork
{
	pthread_mutex_t mutex_fork;
}	t_fork;


long	get_current_time();
long	get_elapsed_time(long ref_time);
void* 	thread_philo(void* arg);
void* 	thread_monitor(void* arg);
int		wait_threads(t_list	*philos, t_data *data);
int		create_threads(t_list	*list, t_data *data);
t_list	*init_philo(t_data	*data);
int		err_and_return_int(char *func, char *msg);