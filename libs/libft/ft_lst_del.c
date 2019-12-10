/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_del.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 18:08:40 by onouaman          #+#    #+#             */
/*   Updated: 2019/12/10 18:08:43 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				ft_lst_free(t_list **st_list)
{
	t_list	*temp;
	t_list	*next;

	if (!st_list || !*st_list)
		return ;
	temp = *st_list;
	while (temp)
	{
		next = temp->next;
		free(temp->content);
		free(temp);
		temp = next;
	}
	*st_list = NULL;
}
