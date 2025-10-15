/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 15:00:51 by mmachida          #+#    #+#             */
/*   Updated: 2025/10/15 18:00:23 by mmachida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <errno.h>
#include "tools.h"

int		add_new_philo(t_list **list, int id, t_data *data);
t_fork	*get_fork_from_idx(t_list *list, int target);

t_list	*init_philo(t_data	*data)
{
	t_list	*philos;
	int		idx;

	idx = 1;
	philos = NULL;
	while (idx < data->num_of_philo + 1)
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
	t_list	*tmp;

	philo = (t_philo *)malloc(sizeof(t_philo));
	if (!philo)
		return (err_and_return_int("add_new_philo"));
	philo->id = id;
	philo->right_fork = get_fork_from_idx(data->forks, id - 1);
	if (id == data->num_of_philo)
		philo->left_fork = get_fork_from_idx(data->forks, 0);
	else
		philo->left_fork = get_fork_from_idx(data->forks, id);
	philo->num_of_meals = 0;
	philo->d = data;
	tmp = ft_lstnew(philo);
	if (!tmp)
		return (err_and_return_int("add_new_philo"));
	ft_lstadd_back(list, tmp);
	return (0);
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
