/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 15:00:51 by mmachida          #+#    #+#             */
/*   Updated: 2025/09/23 15:56:08 by mmachida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <errno.h>
#include "philosopher.h"

int	add_new_philo(t_list **list, int id, t_data *data);

t_list	*init_philo(t_data	*data)
{
	t_list	*philos;
	
	int idx = 0;

	philos = NULL;
	while (idx < NUM_THREADS)
	{
		if (add_new_philo(&philos, idx, data) < 0)
			return (NULL);
		idx++;
	}
	return (philos);
}

int	add_new_philo(t_list **list, int id, t_data *data)
{
	t_philo	*philo;
	t_list 	*tmp;

	philo = (t_philo *)malloc(sizeof(t_philo));
	if (!philo)
		return (err_and_return_int("add_new_philo", strerror(errno)));
	philo->id = id;
	if (pthread_mutex_init(&philo->mutex_philo, NULL) < 0)
		return (err_and_return_int("add_new_philo", strerror(errno)));
	philo->lastmeal_time = data->starttime;
	philo->d = data;
	tmp = ft_lstnew(philo);
	if (!tmp)
		return (err_and_return_int("add_new_philo", strerror(errno)));
	ft_lstadd_back(list, tmp);
	return (0);
}