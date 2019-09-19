/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlcat.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 16:44:10 by onouaman          #+#    #+#             */
/*   Updated: 2018/10/20 01:29:58 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *s1, const char *s2, size_t size)
{
	size_t		i;
	size_t		j;
	size_t		lendst;

	lendst = ft_strlen(s1);
	j = 0;
	i = lendst;
	if (size == 0)
		return (ft_strlen(s2));
	while (s2[j] != '\0' && i < size - 1)
	{
		s1[i] = s2[j];
		i++;
		j++;
	}
	s1[i] = '\0';
	if (size > ft_strlen(s1))
		return (lendst + ft_strlen(s2));
	return (size + ft_strlen(s2));
}
