/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_stat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 13:21:56 by mmachida          #+#    #+#             */
/*   Updated: 2025/10/14 16:14:57 by mmachida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h> // pthread_t
#include <stdio.h> // printf
#include "tools.h"

int	print_stat(t_data *data, int id, char *msg)
{
	long	now;
	int		ret;

	ret = 0;
	pthread_mutex_lock(&data->mutex_print);
	if (!get_stopped(data))
	{
		now = get_elapsed_time(data->starttime);
		printf("%ld %d %s\n", to_ms(now), id, msg);
		ret = -1;
	}
	pthread_mutex_unlock(&data->mutex_print);
	return (ret);
}

int	print_died(t_data *data, int id)
{
	long	now;

	pthread_mutex_lock(&data->mutex_print);
	now = get_elapsed_time(data->starttime);
	printf("%ld %d died\n", to_ms(now), id);
	set_stopped(data, 1);
	pthread_mutex_unlock(&data->mutex_print);
	return (0);
}
