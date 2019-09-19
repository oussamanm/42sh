/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 15:06:10 by onouaman          #+#    #+#             */
/*   Updated: 2018/10/15 15:34:59 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void *v_area;

	if (!(v_area = malloc(size)))
		return (NULL);
	else
	{
		ft_bzero(v_area, size);
		return (v_area);
	}
}
