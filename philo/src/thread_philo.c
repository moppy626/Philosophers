/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 14:04:55 by mmachida          #+#    #+#             */
/*   Updated: 2025/09/24 15:44:53 by mmachida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"
#include <stdio.h>

void* thread_philo(void* arg)
{
	t_philo	*philo = (t_philo *)arg;

	int idx = 0;
	printf("スレッド %d がデータを処理中\n", philo->id);
	while(1)
	{
		usleep(1000);
		if(philo->d->stoped)
			break ;

		// 仮
		//pthread_mutex_lock(&philo->d->mutex_print);
		//pthread_mutex_unlock(&philo->d->mutex_print);

		pthread_mutex_lock(&philo->mutex_philo);
		if (DEBUG)
			printf("thread:%d, idx:%d\n", philo->id, idx);
		idx++;
		pthread_mutex_unlock(&philo->mutex_philo);
	}
    return (NULL);
}