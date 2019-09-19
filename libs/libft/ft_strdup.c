/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strdup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 13:35:27 by onouaman          #+#    #+#             */
/*   Updated: 2019/04/10 17:40:54 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*s2;
	int		lenstr;

	i = 0;
	if (s1 == NULL)
		return (NULL);
	lenstr = ft_strlen(s1);
	s2 = (char *)malloc(sizeof(char) * (lenstr + 1));
	while (i < lenstr)
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}
