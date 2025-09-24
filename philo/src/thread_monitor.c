/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_monitor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 14:03:21 by mmachida          #+#    #+#             */
/*   Updated: 2025/09/24 16:38:21 by mmachida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"
#include <stdio.h>

int	all_full(t_list	*list)
{
	t_list	*tmp;
	t_philo	*philo;

	tmp = list;
	while (tmp)
	{
		philo = (t_philo *)tmp->content;
		if (philo->num_of_meals < philo->d->num_of_eat_time)
			return (0);
	}
	if (DEBUG)
		printf("all stopped\n");
	return (1);
}

void* thread_monitor(void* arg)
{
	t_list	*tmp;
	t_list	*list = (t_list *)arg;
	t_philo	*philo;
	long	time;

	tmp = list;
	while (1)
	{
		if (!tmp)
			tmp = list;
		else
			tmp = tmp->next;
		if (tmp)
		{
			usleep(MONITOR_SLEEP);
			philo = (t_philo *)tmp->content;
			time = get_elapsed_time(philo->lastmeal_time);
			if (DEBUG)
				printf("[thread_monitor]ID:%d time:%ld\n", philo->id, time);
			if (time > philo->d->time_to_die)
			{
				printf("%ld %d died\n", time, philo->id);
				philo->d->stoped = 1;
				break ;
			}
			if (philo->d->specified_eat_time && all_full(list))
				break ;
		}
	}
    return (NULL);
}
