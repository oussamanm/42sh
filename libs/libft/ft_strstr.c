/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 01:44:42 by onouaman          #+#    #+#             */
/*   Updated: 2018/10/20 01:44:45 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int		i;
	int		j;
	size_t	cbfind;
	int		k;

	i = 0;
	if (haystack[0] == '\0' && needle[0] == '\0')
		return ((char *)haystack);
	while (haystack[i] != '\0')
	{
		k = i;
		cbfind = 0;
		j = 0;
		while (needle[j] != '\0')
		{
			if (haystack[k] == needle[j])
				cbfind++;
			j++;
			k++;
		}
		if (cbfind == ft_strlen(needle))
			return ((char *)&haystack[i]);
		i++;
	}
	return ((void *)0);
}
