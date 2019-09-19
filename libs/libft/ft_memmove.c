/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 00:10:39 by onouaman          #+#    #+#             */
/*   Updated: 2019/04/06 20:38:18 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*n_src;
	char	*n_dst;

	i = -1;
	n_src = (char *)src;
	n_dst = (char *)dst;
	if (*n_src == 0 && !(*n_dst == 0))
		return (dst);
	if (n_src == n_dst)
		return (dst);
	else if (n_src < n_dst)
	{
		while (len > 0)
		{
			n_dst[len - 1] = n_src[len - 1];
			len--;
		}
	}
	else
	{
		while (++i < len)
			n_dst[i] = n_src[i];
	}
	return (dst);
}
