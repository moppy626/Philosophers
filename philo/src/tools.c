/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 15:04:53 by mmachida          #+#    #+#             */
/*   Updated: 2025/09/23 17:04:12 by mmachida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	err_and_return_int(char *func, char *msg)
{
	if (func)
		fprintf(stderr, "Failed in %s: %s\n", func, msg);
	else
		fprintf(stderr, "%s\n", msg);
	return (-1);
}