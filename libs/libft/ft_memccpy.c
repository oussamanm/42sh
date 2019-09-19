/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 03:51:33 by onouaman          #+#    #+#             */
/*   Updated: 2018/10/21 19:30:42 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*n_src;
	unsigned char	*n_dst;

	i = 0;
	n_src = (unsigned char *)src;
	n_dst = (unsigned char *)dst;
	while (i < n)
	{
		n_dst[i] = n_src[i];
		if (n_dst[i] == (unsigned char)c)
			return ((n_dst + i + 1));
		i++;
	}
	return (NULL);
}
