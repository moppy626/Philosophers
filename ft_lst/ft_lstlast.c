/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:55:16 by mmachida          #+#    #+#             */
/*   Updated: 2025/09/20 15:13:28 by mmachida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lst.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*work;

	if (!lst)
		return (NULL);
	work = lst;
	while (work->next != NULL)
	{
		work = work->next;
	}
	return (work);
}
