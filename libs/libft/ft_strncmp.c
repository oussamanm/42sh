/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 12:19:38 by onouaman          #+#    #+#             */
/*   Updated: 2018/10/18 22:51:06 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int				r;
	size_t			i;
	unsigned char	*n_s1;
	unsigned char	*n_s2;

	r = 0;
	i = 0;
	n_s1 = (unsigned char *)s1;
	n_s2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	n--;
	while (i < n && n_s1[i] == n_s2[i] && n_s1[i] != '\0' && n_s2[i] != '\0')
		i++;
	return (n_s1[i] - n_s2[i]);
}
