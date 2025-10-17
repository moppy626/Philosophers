/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 14:38:59 by mmachida          #+#    #+#             */
/*   Updated: 2025/10/17 15:53:20 by mmachida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include "tools.h"

void	set_time(t_data	*data, t_list *list);
void	delete_fork(void	*list);
void	delete_data(t_data	*data);
void	delete_philo(void *list);

int	main(int argc, char *argv[])
{
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
	return (0);
}

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
		pthread_mutex_destroy(&data->mutex_init);
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
		pthread_mutex_destroy(&philo->mutex_philo);
		free (philo);
	}
}
