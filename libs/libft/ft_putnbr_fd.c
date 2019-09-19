/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 12:27:47 by onouaman          #+#    #+#             */
/*   Updated: 2018/10/15 12:35:52 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
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
		ft_putchar_fd('-', fd);
	}
	if (n > 9)
	{
		ft_putnbr_fd((n / 10), fd);
		ft_putchar_fd(((n % 10) + b_ismin) + '0', fd);
	}
	else if (n <= 9)
		ft_putchar_fd((n + '0'), fd);
}
