/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_stopped.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 13:59:48 by mmachida          #+#    #+#             */
/*   Updated: 2025/10/09 14:09:30 by mmachida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	set_stopped(t_data *data, int val)
{
	pthread_mutex_lock(&data->mutex_data);
	data->stoped = val;
	pthread_mutex_unlock(&data->mutex_data);
}

int	get_stopped(t_data *data)
{
	int	ret;

	pthread_mutex_lock(&data->mutex_data);
	ret = data->stoped;
	pthread_mutex_unlock(&data->mutex_data);
	return (ret);
}
