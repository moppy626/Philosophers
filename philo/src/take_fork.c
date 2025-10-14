/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 15:20:43 by mmachida          #+#    #+#             */
/*   Updated: 2025/10/14 15:08:43 by mmachida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

t_fork	*get_fork_from_idx(t_list *list, int target);

t_fork	*take_fork(t_philo *philo, int forkid)
{
	t_fork	*fork;

	fork = get_fork_from_idx(philo->d->forks, forkid);
	pthread_mutex_lock(&fork->mutex_fork);
	print_stat(philo->d, philo->id, "has taken a fork");
	return (fork);
}

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
