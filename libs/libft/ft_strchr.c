/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhri <aboukhri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 16:11:05 by onouaman          #+#    #+#             */
/*   Updated: 2019/11/22 06:51:30 by aboukhri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t			i;
	unsigned char	*n_s;
	size_t			len;

	if (!s)
		return (NULL);
	i = 0;
	n_s = (unsigned char *)s;
	len = ft_strlen(s);
	while (i < len)
	{
		if (n_s[i] == '\0' && c == 0)
			return ((char *)&s[i]);
		if (n_s[i] == (unsigned char)c)
			return ((char *)&s[i]);
		i++;
	}
	return (NULL);
}
