/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 18:58:29 by onouaman          #+#    #+#             */
/*   Updated: 2018/10/21 18:49:12 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*temp;

	if (!(temp = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	else
	{
		temp->next = NULL;
		if (content == NULL)
		{
			temp->content = NULL;
			temp->content_size = 0;
			content_size = 0;
		}
		else
		{
			if (!(temp->content = malloc(content_size)))
				return (NULL);
			ft_memcpy(temp->content, content, content_size);
			temp->content_size = content_size;
		}
		return (temp);
	}
}
