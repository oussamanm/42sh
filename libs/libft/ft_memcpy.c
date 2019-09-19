/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 17:55:00 by onouaman          #+#    #+#             */
/*   Updated: 2019/04/06 20:38:37 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*n_dst;
	unsigned char	*n_src;

	i = 0;
	n_dst = (unsigned char *)dst;
	n_src = (unsigned char *)src;
	while (i < n)
	{
		if (n_src[i] == '\0')
			break ;
		n_dst[i] = n_src[i];
		i++;
	}
	return (dst);
}
