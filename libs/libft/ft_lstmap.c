/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 17:10:01 by onouaman          #+#    #+#             */
/*   Updated: 2018/10/21 17:28:05 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f) (t_list *elem))
{
	t_list	*t_first;
	t_list	*t_savenext;
	t_list	*temp1;
	int		i;

	i = 0;
	temp1 = NULL;
	if (!(*(*f)) || !lst)
		return (NULL);
	while (lst)
	{
		temp1 = ft_lstnew(f(lst)->content, f(lst)->content_size);
		if (i++ == 0)
		{
			t_savenext = temp1;
			t_first = temp1;
		}
		else
		{
			t_savenext->next = temp1;
			t_savenext = temp1;
		}
		lst = lst->next;
	}
	return (t_first);
}
