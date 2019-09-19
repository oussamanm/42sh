/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nstrdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 05:03:16 by onouaman          #+#    #+#             */
/*   Updated: 2018/10/20 20:30:14 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_nstrdup(const char *s1, size_t n)
{
	size_t	i;
	char	*s2;
	size_t	lenstr;

	i = 0;
	if (s1 == NULL)
		return (NULL);
	lenstr = ft_strlen(s1);
	s2 = (char *)malloc(sizeof(char) * (n + 1));
	if (s2 == NULL)
		return (NULL);
	while (i < lenstr && i < n)
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}
