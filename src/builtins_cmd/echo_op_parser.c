/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_op_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 15:38:30 by mfilahi           #+#    #+#             */
/*   Updated: 2019/09/26 15:38:40 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		e_fake_option(char *str)
{
	while (*++str)
		if (!(*str == 'n'||\
					*str == 'e' ||\
					*str == 'E'))
			return (1);
	return (0);
}

int		echo_options_(char *arg, int *flag)
{
	while (*arg)
	{
		if (*arg == 'n' && (*flag & e_flg))
			*flag = e_flg | n_flg;
		else if (*arg == 'n')
			*flag = 0 | n_flg;
		else if (*arg == 'n' && ((*flag & n_flg) || (*flag == (n_flg | e_flg))))
			*flag = n_flg | e_flg;
		else if (*arg == 'e' && (*flag & n_flg))
			*flag = e_flg | n_flg;
		else if (*arg == 'e')
			*flag = 0 | e_flg;
		else if (*arg == 'E' && ((*flag & n_flg) || (*flag == (n_flg | e_flg))))
			*flag = 0 | n_flg;
		else if (*arg == 'E')
			*flag = 0 | E_flg;
		arg++;
	}
	return (1);
}

int		echo_options(char **arg, int *flag)
{
	int i;

	i = 0;
	while (arg[i])
	{
		if (arg[i][0] == '-')
		{
			if (e_fake_option(arg[i]))
				return (i);
			echo_options_(&arg[i][1], flag);
		}
		else
			return (i);
		i++;
	}
	return (i);
}
