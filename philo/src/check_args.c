/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 15:02:27 by mmachida          #+#    #+#             */
/*   Updated: 2025/10/14 18:37:48 by mmachida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdio.h>
#include "tools.h"

int	arg_error(char *msg);
int	is_space(char c);
int	check_int(const char *str);

int	check_args(int argc, char *argv[])
{
	int	idx;

	if (!(argc == 5 || argc == 6))
		return (arg_error("The argument must be either 3 or 4"));
	idx = 1;
	while (idx < argc)
	{
		if (check_int(argv[idx]) < 0)
			return (-1);
		idx++;
	}
	if (ft_atoi(argv[1]) > PHILO_MAX)
		return (arg_error("Keep the number of philo at 310 or few"));
	return (0);
}

int	arg_error(char *msg)
{
	printf("%s\n", msg);
	return (-1);
}

/*
	空白を判定する
*/
int	is_space(char c)
{
	if ((9 <= c && c <= 13) || c == 32)
		return (1);
	else
		return (0);
}

/*
	int型に収まる値かどうか調べる
*/
int	check_int(const char *str)
{
	long	num;
	int		i;

	i = 0;
	while (is_space((char)str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			return (arg_error("Argument must be positive value"));
	num = 0;
	if (!('0' <= str[i] && str[i] <= '9'))
		return (arg_error("Argument must be Integer"));
	while (str[i])
	{
		if (!('0' <= str[i] && str[i] <= '9'))
			return (arg_error("Argument must be Integer"));
		else if (num > (INT_MAX - (str[i] - '0')) / 10)
			return (arg_error("Out of int range"));
		num = (num * 10) + (str[i++] - '0');
	}
	return (0);
}
