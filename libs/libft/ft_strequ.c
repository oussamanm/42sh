/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 21:44:58 by onouaman          #+#    #+#             */
/*   Updated: 2018/10/21 01:46:00 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strequ(char const *s1, char const *s2)
{
	size_t			i;
	size_t			lens1;
	size_t			lens2;
	unsigned char	*n_s1;
	unsigned char	*n_s2;

	i = 0;
	n_s1 = (unsigned char *)s1;
	n_s2 = (unsigned char *)s2;
	if (!n_s1 || !n_s2)
		return (0);
	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	while (i < lens1 && i < lens2)
	{
		if (n_s1[i] != n_s2[i])
			return (0);
		else
			i++;
	}
	if (i != lens1 || i != lens2)
		return (0);
	else
		return (1);
}
