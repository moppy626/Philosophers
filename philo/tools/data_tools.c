/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 13:59:48 by mmachida          #+#    #+#             */
/*   Updated: 2025/09/29 14:51:04 by mmachida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	set_stopped(t_data **data, int val)
{
	pthread_mutex_lock(&(*data)->mutex_data);
	(*data)->stoped = val;
	pthread_mutex_unlock(&(*data)->mutex_data);
}

int	get_stopped(t_data *data)
{
	int	ret;

	pthread_mutex_lock(&data->mutex_data);
	ret = data->stoped;
	pthread_mutex_unlock(&data->mutex_data);
	return (ret);
}

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

void	add_fork_waitinglist(t_philo *philo, t_fork *fork)
{
	t_list	*new;

	pthread_mutex_lock(&philo->d->mutex_data);
	new = ft_lstnew(&philo->id);
	ft_lstadd_back(&fork->waiting, new);
	pthread_mutex_unlock(&philo->d->mutex_data);
}

void	upd_fork_waitinglist(t_philo *philo, t_fork *fork)
{
	t_list	*next;

	pthread_mutex_lock(&philo->d->mutex_data);
	next = fork->waiting->next;
	free(fork->waiting);
	fork->waiting = next;
	pthread_mutex_unlock(&philo->d->mutex_data);
}