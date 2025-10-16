/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_num_of_meals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 13:59:48 by mmachida          #+#    #+#             */
/*   Updated: 2025/10/16 10:51:53 by mmachida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	add_num_of_meals(t_philo **philo)
{
	pthread_mutex_lock(&(*philo)->mutex_philo);
	(*philo)->num_of_meals++;
	pthread_mutex_unlock(&(*philo)->mutex_philo);
}

int	get_num_of_meals(t_philo *philo)
{
	int	ret;

	pthread_mutex_lock(&philo->mutex_philo);
	ret = philo->num_of_meals;
	pthread_mutex_unlock(&philo->mutex_philo);
	return (ret);
}
