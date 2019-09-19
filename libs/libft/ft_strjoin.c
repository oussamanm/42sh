/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 11:33:43 by onouaman          #+#    #+#             */
/*   Updated: 2018/10/21 01:47:33 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	lens1;
	size_t	lens2;

	if (!s1 || !s2)
		return (0);
	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	if (!(str = (char *)malloc(sizeof(*str) * (lens1 + lens2 + 1))))
		return (NULL);
	else
	{
		ft_strcpy(str, s1);
		ft_strcpy(str + lens1, s2);
	}
	if (str)
		return (str);
	else
		return (NULL);
}
