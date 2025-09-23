/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_monitor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 14:03:21 by mmachida          #+#    #+#             */
/*   Updated: 2025/09/23 16:24:56 by mmachida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"
#include <stdio.h>

//int	all_full(t_list	*list)
//{
//	t_list	*tmp;
//	t_philo	*philo;

//	tmp = list;
//	while (tmp)
//	{
//		philo = (t_philo *)tmp->content;
//		if (!philo->num_of_meals)
//			return (0);
//	}
//	printf("all stopped\n");
//	return (1);
//}

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
			sleep(1);
			philo = (t_philo *)tmp->content;
			printf("ID:%d\n", philo->id);
			time = get_elapsed_time(philo->lastmeal_time);
			printf("time:%ld\n", time);
			if (time > 5000)
			{
				printf("      Stopped\n");
				philo->d->stoped = 1;
				break ;
			}
			//if (all_full(list))
			//	break ;
		}
	}
    return (NULL);
}