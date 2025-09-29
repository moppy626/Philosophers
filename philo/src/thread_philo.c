/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 14:04:55 by mmachida          #+#    #+#             */
/*   Updated: 2025/09/29 14:55:59 by mmachida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"
#include <stdio.h>

t_fork	*get_fork_from_idx(t_list *list, int target)
{
	t_list	*tmp;
	t_fork	*fork;
	int		idx;

	tmp = list;
	idx = 0;
	while (tmp && idx < target)
	{
		tmp = tmp->next;
		idx++;
	}
	fork = (t_fork *)tmp->content;
	return (fork);
}
t_fork	*take_fork(t_philo *philo, int forkid)
{
	t_fork	*fork;
	int		*topid;

	fork = get_fork_from_idx(philo->d->forks, forkid);
	add_fork_waitinglist(philo, fork);
	while (1)
	{
		usleep(10);
		topid = (int *)fork->waiting->content;
		if (philo->id == *topid)
		{
			upd_fork_waitinglist(philo, fork);
			break ;
		}
	}
	pthread_mutex_lock(&fork->mutex_fork);
	print_stat(philo->d, philo->id, "has taken a fork");
	return (fork);
}

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
	print_stat(philo->d, philo->id, "is eating");
	set_lastmeal_time(&philo, get_current_time());
	wait_micro_s(to_micros(philo->d->time_to_eat), philo->d);
	add_num_of_meals(&philo);
	pthread_mutex_unlock(&right_fork->mutex_fork);
	pthread_mutex_unlock(&left_fork->mutex_fork);
	return (0);
	
}

int	sleeping(t_philo *philo)
{
	print_stat(philo->d, philo->id, "is sleeping");
	wait_micro_s(to_micros(philo->d->time_to_sleep), philo->d);
	return (0);
}

int	thinking(t_philo *philo)
{
	print_stat(philo->d, philo->id, "is thinking");
	return (0);
}

void *thread_philo(void* arg)
{
	t_philo	*philo = (t_philo *)arg;
	int idx = 0;

	if (philo->d->num_of_philo == 1)
	{
		print_stat(philo->d, philo->id, "has taken a fork");
		wait_micro_s(to_micros(philo->d->time_to_die), philo->d);
		return (NULL);
	}
	while(1)
	{
		if(get_stopped(philo->d))
			break ;
		eating(philo);
		if(get_stopped(philo->d))
			return (NULL) ;
		if (philo->d->specified_eat_time &&
			get_num_of_meals(philo) >= philo->d->num_of_eat_time)
			return (NULL);
		sleeping(philo);
		thinking(philo);
		idx++;
	}
    return (NULL);
}

