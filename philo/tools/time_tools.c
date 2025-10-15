/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 15:21:33 by mmachida          #+#    #+#             */
/*   Updated: 2025/10/15 22:12:52 by mmachida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h> // gettimeofday
#include <unistd.h> // NULL
#include <limits.h> // LONG_MAX
#include "tools.h"

long	get_current_time(void)

/*
	現在時刻を取得する(ms)
*/
{
	struct timeval	tv;
	long			tv_sec;
	long			tv_usec;

	if (gettimeofday(&tv, NULL) < 0)
		return (-1);
	tv_sec = tv.tv_sec * 1000000;
	tv_usec = tv.tv_usec;
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
	ret = current - ref_time;
	return (ret);
}

/*
	マイクロ秒で指定された引数分待機する
*/
void	wait_micro_s(long wait_time, t_data *data)
{
	long	start_time;
	long	elapsed_time;

	start_time = get_current_time();
	if (wait_time > REMAIN_TIME)
	{
		while (wait_time != 0)
		{
			elapsed_time = get_elapsed_time(start_time);
			if (elapsed_time >= (wait_time - REMAIN_TIME))
				break ;
			if (get_stopped(data))
				return ;
			usleep(1000);
		}
	}
	while (wait_time != 0)
	{
		elapsed_time = get_elapsed_time(start_time);
		if (elapsed_time >= wait_time)
			break ;
		if (get_stopped(data))
			return ;
		usleep(1);
	}
}

/*
	msからμsに変換する
*/
long	to_ms(long micro_s)
{
	return (micro_s / MICRO_MILI);
}

/*
	μsからmsに変換する
*/
long	to_micros(long mili_s)
{
	return (mili_s * MICRO_MILI);
}
