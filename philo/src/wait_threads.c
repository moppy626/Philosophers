/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 14:55:42 by mmachida          #+#    #+#             */
/*   Updated: 2025/09/23 15:09:11 by mmachida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <errno.h>
#include "philosopher.h"

int	wait_threads(t_list	*philos, t_data *data)
{
	t_philo	*philo;
	t_list	*tmp;
	int		result;

	tmp = philos;
	while(tmp){
		philo = (t_philo *)tmp->content;
    	result = pthread_join(philo->thread, NULL);
		if (result != 0)
			return (err_and_return_int("wait_threads", strerror(errno)));
		tmp = tmp->next;
	}
	result = pthread_join(data->thread_monitor, NULL);
	if (result != 0)
		return (err_and_return_int("wait_threads", strerror(errno)));
	return (0);
}