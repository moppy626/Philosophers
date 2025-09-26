/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 15:00:51 by mmachida          #+#    #+#             */
/*   Updated: 2025/09/25 12:45:43 by mmachida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <errno.h>
#include "philosopher.h"
#include "tools.h"

int	add_new_philo(t_list **list, int id, t_data *data);

t_list	*init_philo(t_data	*data)
{
	t_list	*philos;
	
	int idx = 1;

	philos = NULL;
	while (idx < data->num_of_philo + 1)
	{
		if (add_new_philo(&philos, idx, data) < 0)
			return (NULL);
		idx++;
	}
	return (philos);
}

#include <stdio.h>
int	add_new_philo(t_list **list, int id, t_data *data)
{
	t_philo	*philo;
	t_list 	*tmp;

	philo = (t_philo *)malloc(sizeof(t_philo));
	if (!philo)
		return (err_and_return_int("add_new_philo"));
	philo->id = id;
	philo->right_fork = id - 1;
	if (id == data->num_of_philo)
		philo->left_fork = 0;
	else
		philo->left_fork = id;
	//printf("id:%d right:%d left:%d\n", philo->id, philo->right_fork, philo->left_fork);
	philo->lastmeal_time = data->starttime;
	philo->num_of_meals = 0;
	philo->d = data;
	tmp = ft_lstnew(philo);
	if (!tmp)
		return (err_and_return_int("add_new_philo"));
	ft_lstadd_back(list, tmp);
	return (0);
}
