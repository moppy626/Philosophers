/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 14:04:55 by mmachida          #+#    #+#             */
/*   Updated: 2025/09/28 23:21:54 by mmachida         ###   ########.fr       */
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

int	eating(t_philo *philo)
{
	t_fork	*right_fork;
	t_fork	*left_fork;

	right_fork = get_fork_from_idx(philo->d->forks, philo->right_fork);
	pthread_mutex_lock(&right_fork->mutex_fork);
	print_stat(philo->d, philo->id, "has taken a fork");
	left_fork = get_fork_from_idx(philo->d->forks, philo->left_fork);
	pthread_mutex_lock(&left_fork->mutex_fork);
	print_stat(philo->d, philo->id, "has taken a fork");
	print_stat(philo->d, philo->id, "is eating");
	set_lastmeal_time(&philo, get_current_time());
	wait_micro_s(to_micros(philo->d->time_to_eat));
	add_num_of_meals(&philo);
	pthread_mutex_unlock(&right_fork->mutex_fork);
	pthread_mutex_unlock(&left_fork->mutex_fork);
	return (0);
	
}

int	sleeping(t_philo *philo)
{
	print_stat(philo->d, philo->id, "is sleeping");
	wait_micro_s(to_micros(philo->d->time_to_sleep));
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
	
	//printf("スレッド %d がデータを処理中\n", philo->id);
	if (philo->d->num_of_philo == 1)
	{
		print_stat(philo->d, philo->id, "has taken a fork");
		wait_micro_s(to_micros(philo->d->time_to_die));
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

