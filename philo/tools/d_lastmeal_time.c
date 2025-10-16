/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_lastmeal_time.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 13:59:48 by mmachida          #+#    #+#             */
/*   Updated: 2025/10/16 10:51:30 by mmachida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	set_lastmeal_time(t_philo **philo, long val)
{
	pthread_mutex_lock(&(*philo)->mutex_philo);
	(*philo)->lastmeal_time = val;
	pthread_mutex_unlock(&(*philo)->mutex_philo);
}

long	get_lastmeal_time(t_philo *philo)
{
	long	ret;

	pthread_mutex_lock(&philo->mutex_philo);
	ret = philo->lastmeal_time;
	pthread_mutex_unlock(&philo->mutex_philo);
	return (ret);
}
