/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 14:38:59 by mmachida          #+#    #+#             */
/*   Updated: 2025/09/28 23:20:51 by mmachida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include "tools.h"

void	delete_fork(void	*list)
{
	t_fork	*fork;

	fork = (t_fork *)list;
	if (fork)
	{
		pthread_mutex_destroy(&fork->mutex_fork);
		free (fork);
	}
}

void	delete_data(t_data	*data)
{
	if (data)
	{
		pthread_mutex_destroy(&data->mutex_print);
		pthread_mutex_destroy(&data->mutex_data);
		ft_lstclear(&data->forks, &delete_fork);
		free (data);
	}
}

void	delete_philo(void *list)
{
	t_philo	*philo;

	philo = (t_philo *)list;
	if (philo)
	{
		free (philo);
	}
}

 int		init_forks(t_data	*data)
 {
	int				idx;
	t_fork			*fork;
	t_list			*tmp;

	idx = 0;
	data->forks = NULL;
	while(idx < data->num_of_philo)
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

void		set_args(t_data	**data, int argc, char *argv[])
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

t_data	*init_data(int argc, char *argv[])
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->stoped = 0;
	data->starttime = get_current_time();
	set_args(&data, argc, argv);
 	if (pthread_mutex_init(&data->mutex_print, NULL) < 0)
 		return (err_and_return_NULL("init_data"));
	if (pthread_mutex_init(&data->mutex_data, NULL) < 0)
		return (err_and_return_NULL("init_data"));
	if (init_forks(data) < 0)
		return (NULL);
	return (data);
}

int	arg_error(char *msg)
{
	printf("%s\n", msg);
	return (-1);
}

int	check_args(int argc, char *argv[])
{
	(void)argv;
	if(!(argc == 5 || argc == 6))
		return (arg_error("The argument must be either 3 or 4"));
	return (0);
}

int main(int argc, char *argv[]) {
	t_data	*data;
	t_list	*philos;

	printf("argc:%d, argv[%d]:%s\n", argc, argc - 1, argv[argc - 1]);
	if (check_args(argc, argv) < 0)
		return (-1);
	data = init_data(argc, argv);
	if (!data)
		return (-1);
	philos = init_philo(data);
	if (!philos)
		return (-1);
	if (create_threads(philos, data) < 0)
		return (-1);
	if (wait_threads(philos, data) < 0)
		return (-1);
	delete_data(data);
	ft_lstclear(&philos, delete_philo);
    return 0;
}
