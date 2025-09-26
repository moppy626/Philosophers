/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 14:58:25 by mmachida          #+#    #+#             */
/*   Updated: 2025/09/25 11:54:47 by mmachida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <errno.h>
#include "philosopher.h"
#include "tools.h"

int	create_threads(t_list	*list, t_data *data)
{
	t_philo	*philo;
	t_list	*tmp;
	int		result;

	tmp = list;
	while(tmp)
	{
		philo = tmp->content;
		result = pthread_create(&philo->thread, NULL, thread_philo, philo);
		if (result != 0)
			return (err_and_return_int("create_threads"));
		tmp = tmp->next;
	}
	result = pthread_create(&data->thread_monitor, NULL, thread_monitor, list);
	if (result != 0)
		return (err_and_return_int("create_threads"));
	return (0);
}