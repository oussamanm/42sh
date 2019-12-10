/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 01:24:33 by onouaman          #+#    #+#             */
/*   Updated: 2019/12/10 01:24:35 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_lstfind(t_list *st_list, char *content)
{
	if (!st_list || !content)
		return (0);
	while (st_list)
	{
		if (ft_strcmp((char *)st_list->content, content) == 0)
			return (1);
		st_list = st_list->next;
	}
	return (0);
}
