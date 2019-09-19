/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strncpy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 15:00:30 by onouaman          #+#    #+#             */
/*   Updated: 2018/10/19 21:02:32 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t			i;
	size_t			lensrc;
	unsigned char	*n_dst;
	unsigned char	*n_src;

	i = 0;
	if (dst == NULL || src == NULL)
		return (NULL);
	n_dst = (unsigned char *)dst;
	n_src = (unsigned char *)src;
	lensrc = ft_strlen(src);
	while (i < lensrc && i < len)
	{
		n_dst[i] = n_src[i];
		i++;
	}
	lensrc = ft_strlen(dst);
	while (i < lensrc)
	{
		n_dst[i] = 0;
		i++;
	}
	return (dst);
}
