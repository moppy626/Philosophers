/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 12:26:29 by mmachida          #+#    #+#             */
/*   Updated: 2025/09/21 15:21:02 by mmachida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lst.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*work;

	if (!lst || !(*lst))
	{
		*lst = new;
		return ;
	}
	else
	{
		work = ft_lstlast(*lst);
		work->next = new;
	}
}
