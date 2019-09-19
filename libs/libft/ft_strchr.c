/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 16:11:05 by onouaman          #+#    #+#             */
/*   Updated: 2018/10/20 01:42:57 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t			i;
	unsigned char	*n_s;

	i = 0;
	n_s = (unsigned char *)s;
	while (i <= ft_strlen((const char *)n_s))
	{
		if (n_s[i] == '\0' && c == 0)
			return ((char *)&s[i]);
		if (n_s[i] == (unsigned char)c)
			return ((char *)&s[i]);
		i++;
	}
	return (NULL);
}
