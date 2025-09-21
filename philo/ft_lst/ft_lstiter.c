/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:23:22 by mmachida          #+#    #+#             */
/*   Updated: 2025/09/21 15:21:10 by mmachida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lst.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*work;

	if (!lst || !f)
		return ;
	work = lst;
	while (work != NULL)
	{
		f(work->content);
		work = work->next;
	}
}
