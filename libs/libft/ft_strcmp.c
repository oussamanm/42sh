/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 12:06:14 by onouaman          #+#    #+#             */
/*   Updated: 2018/10/09 19:15:21 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	int				r;
	int				i;
	unsigned char	*n_s1;
	unsigned char	*n_s2;

	r = 0;
	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (-1);
	n_s1 = (unsigned char *)s1;
	n_s2 = (unsigned char *)s2;
	while (n_s1[i] == n_s2[i] && n_s1[i] != '\0')
		i++;
	r = n_s1[i] - n_s2[i];
	return (r);
}
