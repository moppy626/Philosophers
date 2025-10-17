/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 14:04:55 by mmachida          #+#    #+#             */
/*   Updated: 2025/10/17 16:16:37 by mmachida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"
#include <stdio.h>

int		eating(t_philo *philo);
int		sleeping(t_philo *philo);
int		thinking(t_philo *philo);
void	wait_while_init_philo(t_philo *philo);

void	*thread_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_while_init_philo(philo);
	if (philo->d->num_of_philo == 1)
	{
		print_stat(philo->d, philo->id, "has taken a fork");
		wait_micro_s(getnow(), to_micros(philo->d->time_to_die), philo->d);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		wait_micro_s(get_lastmeal_time(philo),
			to_micros(philo->d->time_to_eat) / 2, philo->d);
	while (1)
	{
		if (eating(philo))
			return (NULL);
		if (sleeping(philo))
			return (NULL);
		if (thinking(philo))
			return (NULL);
	}
	return (NULL);
}

int	eating(t_philo *philo)
{
	t_fork	*right_fork;
	t_fork	*left_fork;

	if (philo->id == philo->d->num_of_philo)
	{
		right_fork = take_fork(philo, philo->right_fork);
		left_fork = take_fork(philo, philo->left_fork);
	}
	else
	{
		left_fork = take_fork(philo, philo->left_fork);
		right_fork = take_fork(philo, philo->right_fork);
	}
	set_lastmeal_time(&philo, getnow());
	print_stat(philo->d, philo->id, "is eating");
	wait_micro_s(get_lastmeal_time(philo),
		to_micros(philo->d->time_to_eat), philo->d);
	add_num_of_meals(&philo);
	pthread_mutex_unlock(&right_fork->mutex_fork);
	pthread_mutex_unlock(&left_fork->mutex_fork);
	return (get_stopped(philo->d));
}

int	sleeping(t_philo *philo)
{
	long	start_time;

	start_time = get_lastmeal_time(philo) + to_micros(philo->d->time_to_eat);
	print_stat(philo->d, philo->id, "is sleeping");
	wait_micro_s(start_time, to_micros(philo->d->time_to_sleep), philo->d);
	return (get_stopped(philo->d));
}

int	thinking(t_philo *philo)
{
	long	start_time;

	start_time = get_lastmeal_time(philo) + to_micros(philo->d->time_to_eat)
		+ to_micros(philo->d->time_to_sleep);
	print_stat(philo->d, philo->id, "is thinking");
	if (philo->d->num_of_philo % 2 == 1)
		wait_micro_s(start_time,
			to_micros(philo->d->time_to_eat) / 10, philo->d);
	return (get_stopped(philo->d));
}

void	wait_while_init_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->d->mutex_init);
	pthread_mutex_unlock(&philo->d->mutex_init);
}
