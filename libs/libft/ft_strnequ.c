/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 22:20:09 by onouaman          #+#    #+#             */
/*   Updated: 2018/10/11 22:34:41 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int		ft_strnequ(char const *s1, char const *s2, size_t n)
{
	size_t			i;
	unsigned char	*n_s1;
	unsigned char	*n_s2;

	i = 0;
	n_s1 = (unsigned char *)s1;
	n_s2 = (unsigned char *)s2;
	if (!n_s1 || !n_s2)
		return (0);
	while (n_s1 && n_s2 && i < n)
	{
		if (n_s1[i] != n_s2[i])
			return (0);
		i++;
	}
	if (i < n)
		return (0);
	else
		return (1);
}
