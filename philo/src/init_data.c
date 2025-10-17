/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 15:05:20 by mmachida          #+#    #+#             */
/*   Updated: 2025/10/17 15:20:26 by mmachida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "tools.h"

int		init_forks(t_data	*data);
void	set_args(t_data	**data, int argc, char *argv[]);

t_data	*init_data(int argc, char *argv[])
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->stoped = 0;
	set_args(&data, argc, argv);
	if (pthread_mutex_init(&data->mutex_print, NULL) < 0)
		return (err_and_return_null("init_data"));
	if (pthread_mutex_init(&data->mutex_data, NULL) < 0)
		return (err_and_return_null("init_data"));
	if (pthread_mutex_init(&data->mutex_init, NULL) < 0)
		return (err_and_return_null("init_data"));
	if (init_forks(data) < 0)
		return (NULL);
	return (data);
}

int	init_forks(t_data	*data)
{
	int				idx;
	t_fork			*fork;
	t_list			*tmp;

	idx = 0;
	data->forks = NULL;
	while (idx < data->num_of_philo)
	{
		fork = malloc(sizeof(t_fork));
		if (pthread_mutex_init(&fork->mutex_fork, NULL) < 0)
			return (err_and_return_int("init_forks"));
		tmp = ft_lstnew(fork);
		if (!tmp)
			return (err_and_return_int("init_forks"));
		ft_lstadd_back(&data->forks, tmp);
		idx++;
	}
	return (0);
}

void	set_args(t_data	**data, int argc, char *argv[])
{
	(*data)->num_of_philo = ft_atoi(argv[1]);
	(*data)->time_to_die = ft_atoi(argv[2]);
	(*data)->time_to_eat = ft_atoi(argv[3]);
	(*data)->time_to_sleep = ft_atoi(argv[4]);
	if (argc >= 6)
	{
		(*data)->specified_eat_time = 1;
		(*data)->num_of_eat_time = ft_atoi(argv[5]);
	}
	else
	{
		(*data)->specified_eat_time = 0;
		(*data)->num_of_eat_time = 0;
	}
	if (DEBUG)
	{
		printf("   num_of_philo:%d\n", (*data)->num_of_philo);
		printf("   time_to_die:%d\n", (*data)->time_to_die);
		printf("   time_to_eat:%d\n", (*data)->time_to_eat);
		printf("   time_to_sleep:%d\n", (*data)->time_to_sleep);
		printf("   num_of_eat_time:%d\n", (*data)->num_of_eat_time);
	}
}
