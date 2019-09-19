/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strnstr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 21:20:07 by onouaman          #+#    #+#             */
/*   Updated: 2018/10/20 01:50:12 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *hays, const char *need, size_t len)
{
	int		i;
	int		j;
	size_t	k;
	size_t	cpfind;

	i = 0;
	if (hays[0] == '\0' && need[0] == '\0')
		return ((char *)hays);
	while (hays[i] != '\0')
	{
		cpfind = 0;
		j = 0;
		k = i;
		while (need[j] != '\0' && k < len)
		{
			if (need[j] == hays[k])
				cpfind++;
			k++;
			j++;
		}
		if (cpfind == ft_strlen(need))
			return ((char *)&hays[i]);
		i++;
	}
	return ((void *)0);
}
