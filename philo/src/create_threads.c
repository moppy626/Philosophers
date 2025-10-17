/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 14:58:25 by mmachida          #+#    #+#             */
/*   Updated: 2025/10/17 15:53:36 by mmachida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <errno.h>
#include "tools.h"

void	set_time(t_data	*data, t_list *list);

int	create_threads(t_list	*list, t_data *data)
{
	t_philo	*philo;
	t_list	*tmp;
	int		result;

	tmp = list;
	pthread_mutex_lock(&data->mutex_init);
	while (tmp)
	{
		philo = tmp->content;
		result = pthread_create(&philo->thread, NULL, thread_philo, philo);
		if (result != 0)
			return (err_and_return_int("create_threads"));
		tmp = tmp->next;
	}
	set_time(data, list);
	result = pthread_create(&data->thread_monitor, NULL, thread_monitor, list);
	if (result != 0)
		return (err_and_return_int("create_threads"));
	pthread_mutex_unlock(&data->mutex_init);
	return (0);
}

void	set_time(t_data	*data, t_list *list)
{
	t_philo	*philo;
	t_list	*tmp;

	data->starttime = getnow();
	tmp = list;
	while (tmp)
	{
		philo = tmp->content;
		philo->lastmeal_time = data->starttime;
		tmp = tmp->next;
	}
}
