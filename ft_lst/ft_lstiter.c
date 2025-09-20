/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:23:22 by mmachida          #+#    #+#             */
/*   Updated: 2025/09/20 15:13:25 by mmachida         ###   ########.fr       */
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
