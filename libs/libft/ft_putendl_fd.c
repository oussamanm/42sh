/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 12:24:55 by onouaman          #+#    #+#             */
/*   Updated: 2018/10/15 13:08:43 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_putendl_fd(char const *s, int fd)
{
	int rtn;

	// ft_putstr_fd("୧༼ಠ益ಠ༽︻╦╤─ :: ", 2);
	rtn = ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
	return (rtn + 1);
}
