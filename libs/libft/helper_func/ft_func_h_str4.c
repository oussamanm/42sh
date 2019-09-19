/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_func_h_str4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 19:26:13 by onouaman          #+#    #+#             */
/*   Updated: 2019/08/07 19:26:15 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_isalldigit(char *str)
{
	if (str == NULL)
		return (0);
	while (*str != '\0')
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

int		ft_isallalphanum(char *str)
{
	if (str == NULL)
		return (0);
	while (*str != '\0')
	{
		if (!ft_isalphanum(*str))
			return (0);
		str++;
	}
	return (1);
}

int		ft_isallprint(char *str)
{
	if (str == NULL)
		return (0);
	while (*str != '\0')
	{
		if (!ft_isprint(*str))
			return (0);
		str++;
	}
	return (1);
}
