/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_countw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 03:03:46 by onouaman          #+#    #+#             */
/*   Updated: 2018/10/20 03:24:00 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_countw(const char *str, char c)
{
	int i;
	int i_resu;
	int i_nega;

	i_resu = 0;
	i = 0;
	if (!str)
		return (0);
	if (str[0] == c)
		i_nega = 0;
	else if (str[0] != c)
		i_nega = 1;
	while (str[i] != '\0')
	{
		if (str[i] != c && i_nega == 1)
		{
			i_nega = 0;
			i_resu++;
		}
		else if (str[i] == c && i_nega == 0)
			i_nega = 1;
		i++;
	}
	return (i_resu);
}
