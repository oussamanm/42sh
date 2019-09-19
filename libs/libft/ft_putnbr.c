/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 11:56:07 by onouaman          #+#    #+#             */
/*   Updated: 2018/10/15 12:13:50 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n)
{
	int b_ismin;

	b_ismin = 0;
	if (n < 0)
	{
		if (n == -2147483648)
		{
			n++;
			b_ismin = 1;
		}
		n = n * -1;
		ft_putchar('-');
	}
	if (n > 9)
	{
		ft_putnbr(n / 10);
		ft_putchar(((n % 10) + b_ismin) + '0');
	}
	else if (n <= 9)
		ft_putchar(n + '0');
}
