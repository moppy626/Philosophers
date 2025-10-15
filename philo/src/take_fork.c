/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 15:20:43 by mmachida          #+#    #+#             */
/*   Updated: 2025/10/15 17:58:38 by mmachida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

t_fork	*take_fork(t_philo *philo, t_fork *fork)
{
	pthread_mutex_lock(&fork->mutex_fork);
	print_stat(philo->d, philo->id, "has taken a fork");
	return (fork);
}
