/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 12:21:00 by onouaman          #+#    #+#             */
/*   Updated: 2018/10/21 17:25:58 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_putstr_fd(char const *s, int fd)
{
	int len;

	if (!s)
		return (0);
	len = ft_strlen(s);
	len = write (fd, s, len);
	return (len);
}
