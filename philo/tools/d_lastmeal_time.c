/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_tools copy 2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 13:59:48 by mmachida          #+#    #+#             */
/*   Updated: 2025/09/29 15:25:21 by mmachida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	set_lastmeal_time(t_philo **philo, long val)
{
	pthread_mutex_lock(&(*philo)->d->mutex_data);
	(*philo)->lastmeal_time = val;
	pthread_mutex_unlock(&(*philo)->d->mutex_data);
}

long	get_lastmeal_time(t_philo *philo)
{
	long	ret;

	pthread_mutex_lock(&philo->d->mutex_data);
	ret = philo->lastmeal_time;
	pthread_mutex_unlock(&philo->d->mutex_data);
	return (ret);
}
