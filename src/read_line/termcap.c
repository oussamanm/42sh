/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlamhidr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 17:19:50 by hlamhidr          #+#    #+#             */
/*   Updated: 2019/04/05 17:19:51 by hlamhidr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_line.h"

int		my_outc(int c)
{
	ft_putchar(c);
	return (1);
}

void	ft_disable(void)
{
	if (tcsetattr(0, TCSANOW, &g_pos.disable) == ERR)
		ft_err_exit("ERROR in seting Temcap parameters");
}

void	ft_enable(void)
{
	if (tcsetattr(0, TCSANOW, &g_pos.enable) == ERR)
		ft_err_exit("ERROR in seting Temcap parameters");
}

int		ft_set_termcap(void)
{
	if (tgetent(NULL, getenv("TERM")) != 1)
		return (-1);
	if (tcgetattr(0, &g_pos.enable) == ERR)
		return (-1);
	if (tcgetattr(0, &g_pos.disable) == ERR)
		return (-1);
	g_pos.enable.c_lflag &= ~(ICANON);
	g_pos.enable.c_lflag &= ~(ECHO);
	return (0);
}
