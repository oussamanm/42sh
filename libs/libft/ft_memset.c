/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 10:32:14 by onouaman          #+#    #+#             */
/*   Updated: 2018/10/19 19:27:44 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	char			*t;
	size_t			i;
	unsigned char	ch;

	i = 0;
	ch = c;
	t = (char *)s;
	while (i < n)
	{
		t[i] = ch;
		i++;
	}
	return (t);
}
