/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_monitor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 14:03:21 by mmachida          #+#    #+#             */
/*   Updated: 2025/09/29 15:42:13 by mmachida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"
#include <stdio.h>

int	all_full(t_list	*list)
{
	t_list	*tmp;
	t_philo	*philo;

	tmp = list;
	while (tmp)
	{
		philo = (t_philo *)tmp->content;
		if (get_num_of_meals(philo) < philo->d->num_of_eat_time)
			return (0);
		tmp = tmp->next;
	}
	if (DEBUG)
		printf("all stopped\n");
	return (1);
}

void	*thread_monitor(void *arg)
{
	t_list	*tmp;
	t_list	*list;
	t_philo	*philo;

	list = (t_list *)arg;
	tmp = list;
	while (1)
	{
		tmp = tmp->next;
		if (!tmp)
			tmp = list;
		philo = (t_philo *)tmp->content;
		if (get_elapsed_time(get_lastmeal_time(philo))
			>= (to_micros(philo->d->time_to_die)))
		{
			print_stat(philo->d, philo->id, "died");
			set_stopped(&philo->d, 1);
			break ;
		}
		if (philo->d->specified_eat_time && all_full(list))
			break ;
		wait_micro_s(10, philo->d);
	}
	return (NULL);
}
