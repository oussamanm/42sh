/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/14 20:34:05 by onouaman          #+#    #+#             */
/*   Updated: 2019/04/06 20:45:47 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void				ft_nega(long long int n, long long int *n_nbr,
		int *n_nega, int *i_ismin)
{
	*n_nega = 1;
	*n_nbr = n;
	*i_ismin = 0;
	if (n < 0)
	{
		*n_nega = -1;
		if (n == -2147483648)
		{
			*i_ismin = 1;
			*n_nbr = (n + 1) * -1;
		}
		else
			*n_nbr = n * -1;
	}
}

static	long long int	ft_strleni(long long int nb)
{
	long long int resu;

	resu = 0;
	if (nb < 0)
	{
		if (nb == -2147483648)
			nb++;
		resu++;
		nb = nb * -1;
	}
	if (nb == 0)
		resu++;
	while (nb > 0)
	{
		nb = nb / 10;
		resu++;
	}
	return (resu);
}

char					*ft_itoa(long long int n)
{
	long long int	lennbr;
	long long int	n_nbr;
	int				n_nega;
	int				i_ismin;
	char			*str;

	lennbr = ft_strleni(n);
	str = ft_strnew(lennbr);
	ft_nega(n, &n_nbr, &n_nega, &i_ismin);
	str[lennbr] = '\0';
	lennbr--;
	while (lennbr >= 0)
	{
		if (lennbr == 0 && n_nega < 0)
			str[lennbr] = '-';
		else if (lennbr == (ft_strleni(n) - 1) && i_ismin == 1)
			str[lennbr] = ((n_nbr % 10) + 1) + '0';
		else
			str[lennbr] = (n_nbr % 10) + '0';
		n_nbr = n_nbr / 10;
		lennbr--;
	}
	return (str);
}
