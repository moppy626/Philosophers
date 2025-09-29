/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 15:04:53 by mmachida          #+#    #+#             */
/*   Updated: 2025/09/29 15:49:57 by mmachida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	err_and_return_int(char *func, char *msg)
{
	if (func)
		fprintf(stderr, "Failed in %s\n", func);
	if (msg)
		fprintf(stderr, "%s\n", msg);
	return (-1);
}

void	*err_and_return_null(char *func)
{
	if (func)
		fprintf(stderr, "Failed in %s\n", func);
	return (NULL);
}
