/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_tools copy 3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 13:59:48 by mmachida          #+#    #+#             */
/*   Updated: 2025/09/29 15:25:40 by mmachida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	add_num_of_meals(t_philo **philo)
{
	pthread_mutex_lock(&(*philo)->d->mutex_data);
	(*philo)->num_of_meals++;
	pthread_mutex_unlock(&(*philo)->d->mutex_data);
}

int	get_num_of_meals(t_philo *philo)
{
	int	ret;

	pthread_mutex_lock(&philo->d->mutex_data);
	ret = philo->num_of_meals;
	pthread_mutex_unlock(&philo->d->mutex_data);
	return (ret);
}
