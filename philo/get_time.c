/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 15:21:33 by mmachida          #+#    #+#             */
/*   Updated: 2025/09/21 15:21:37 by mmachida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h> // gettimeofday
#include <unistd.h> // NULL
#include <limits.h> // LONG_MAX
/*
	現在時刻を取得する(ms)
*/
long	get_current_time()
{
	struct timeval	tv;
	long			tv_sec;
	long			tv_usec;

	if (gettimeofday(&tv, NULL) < 0)
		return (-1);
	tv_sec = tv.tv_sec * 1000;
	tv_usec = tv.tv_usec / 1000;
	return (tv_sec + tv_usec);
}
/*
	パラメタの時刻からの経過時間を取得する(ms)
*/
long	get_elapsed_time(long ref_time)
{
	long	current;
	long	ret;

	current = get_current_time();
	if (current < 0)
		return (-1);
	if (-current > LONG_MAX - ref_time)
		return (-1);
	ret = current - ref_time;
	return (ret);
}