/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 14:04:55 by mmachida          #+#    #+#             */
/*   Updated: 2025/10/09 14:42:48 by mmachida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"
#include <stdio.h>

int	eating(t_philo *philo)
{
	t_fork	*right_fork;
	t_fork	*left_fork;

	if (philo->id % 2 == 0)
	{
		right_fork = take_fork(philo, philo->right_fork);
		left_fork = take_fork(philo, philo->left_fork);
	}
	else
	{
		left_fork = take_fork(philo, philo->left_fork);
		right_fork = take_fork(philo, philo->right_fork);
	}
	if (!print_stat(philo->d, philo->id, "is eating"))
	{
		set_lastmeal_time(&philo, get_current_time());
		wait_micro_s(to_micros(philo->d->time_to_eat), philo->d);
		add_num_of_meals(&philo);
	}
	pthread_mutex_unlock(&right_fork->mutex_fork);
	pthread_mutex_unlock(&left_fork->mutex_fork);
	return (0);
}

int	sleeping(t_philo *philo)
{
	int	ret;

	ret = print_stat(philo->d, philo->id, "is sleeping");
	wait_micro_s(to_micros(philo->d->time_to_sleep), philo->d);
	return (0);
}

int	thinking(t_philo *philo)
{
	print_stat(philo->d, philo->id, "is thinking");
	return (0);
}

void	*thread_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->d->num_of_philo == 1)
	{
		print_stat(philo->d, philo->id, "has taken a fork");
		wait_micro_s(to_micros(philo->d->time_to_die), philo->d);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		wait_micro_s(50, philo->d);
	while (1)
	{
		if (get_stopped(philo->d))
			break ;
		eating(philo);
		if (get_stopped(philo->d))
			return (NULL);
		sleeping(philo);
		if (get_stopped(philo->d))
			return (NULL);
		thinking(philo);
	}
	return (NULL);
}
