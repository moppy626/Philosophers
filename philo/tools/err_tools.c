/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 15:04:53 by mmachida          #+#    #+#             */
/*   Updated: 2025/09/25 11:49:38 by mmachida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	err_and_return_int(char *func)
{
	if (func)
		fprintf(stderr, "Failed in %s\n", func);
	return (-1);
}

void	*err_and_return_NULL(char *func)
{
	if (func)
		fprintf(stderr, "Failed in %s\n", func);
	return (NULL);
}