/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 14:38:59 by mmachida          #+#    #+#             */
/*   Updated: 2025/09/23 17:05:56 by mmachida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include "philosopher.h"
#include "tools.h"

void	delete_data(t_data	*data)
{
	if (data)
		free (data);
}

void	delete_philo(void *list)
{
	t_philo	*philo;

	philo = (t_philo *)list;
	if (philo)
	{
		//if (philo->thread)
		//	free(philo->thread);
		pthread_mutex_destroy(&philo->mutex_philo);
		free (philo);
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
	data->num_of_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc >= 5)
	{
		data->specified_eat_time = 1;
		data->num_of_eat_time = ft_atoi(argv[5]);
	}
	else
	{
		data->specified_eat_time = 0;
		data->num_of_eat_time = 0;
	}
	return (data);
}

int	check_args(int argc, char *argv[])
{
	(void)argv;
	if(!(argc == 3 || argc == 4))
		return (err_and_return_int(NULL, "The argument must be either 3 or 4"));
	return (0);
}

int main(int argc, char *argv[]) {
	t_data	*data;
	t_list	*philos;

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
