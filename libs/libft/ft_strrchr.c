/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 17:12:24 by onouaman          #+#    #+#             */
/*   Updated: 2018/10/15 17:48:07 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t			i;
	int				i_find;
	unsigned char	*n_s;

	i = 0;
	i_find = -1;
	n_s = (unsigned char *)s;
	while (i <= ft_strlen((const char *)n_s))
	{
		if (n_s[i] == '\0' && c == 0)
			i_find = i;
		else if (n_s[i] == (unsigned char)c)
			i_find = i;
		i++;
	}
	if (i_find != -1)
		return ((char *)&s[i_find]);
	else
		return (NULL);
}
