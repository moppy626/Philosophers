/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_fork_waitinglist.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 13:59:48 by mmachida          #+#    #+#             */
/*   Updated: 2025/09/29 15:34:45 by mmachida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

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
