/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 12:25:29 by onouaman          #+#    #+#             */
/*   Updated: 2018/10/21 00:40:52 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_isnbr(char s)
{
	return (s >= 48 && s <= 57);
}

static	int	ft_iswtspace(char s)
{
	return ((s >= 9 && s <= 13) || s == 32);
}

int			ft_atoi(const char *str)
{
	int i;
	int r;
	int b_nega;

	i = 0;
	r = 0;
	b_nega = 1;
	while (str[i] != '\0')
	{
		while (ft_iswtspace(str[i]) && r == 0)
			i++;
		if (ft_isnbr(str[i]))
			r = r * 10 + (str[i] - '0');
		else if ((str[i] == '-' || str[i] == '+') && !ft_isnbr(str[i + 1]))
			return (0);
		else if (str[i] == '-' && r < 1)
			b_nega = -1;
		else if (str[i] == '+' && r < 1)
			b_nega = b_nega + 0;
		else
			break ;
		i++;
	}
	return (r * b_nega);
}
