/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_built.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 12:17:27 by mfilahi           #+#    #+#             */
/*   Updated: 2019/11/15 18:28:34 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** - check of metacharacters;
*/

int		echo_meta_char(char c)
{
	if (c == 'a')
		return ('\a');
	else if (c == 'b')
		return ('\b');
	else if (c == 'f')
		return ('\f');
	else if (c == 'n')
		return ('\n');
	else if (c == 'r')
		return ('\r');
	else if (c == 't')
		return ('\t');
	else if (c == 'v')
		return ('\v');
	else if (c == '\\')
		return ('\\');
	return (c);
}

/*
** - comparison of chars;
*/

char	echo_charcmp(char c, char *str)
{
	while (*str)
	{
		if (*str++ == c)
			return (echo_meta_char(c));
	}
	return (c);
}

/*
** this functinon serve option echo -n;
*/

void	n_flag(char *arg, int flag)
{
	(flag) ? ft_putstr(arg) : 0;
	if (arg[ft_strlen(arg) - 1] != '\n')
	{
		ft_putstr_fd("\033[7m", 1);
		ft_putchar_fd('%', 1);
		ft_putstr_fd("\033[m\n", 1);
	}
}

/*
** this functinon serve option echo -e;
*/

void	e_interpretation(char *arg, int flag)
{
	char	tmp;
	char	*temp;
	int		i;

	i = -1;
	while (arg[++i])
	{
		if (arg[i] == '\\')
		{
			tmp = arg[i + 1];
			arg[i + 1] = echo_charcmp(arg[i + 1], "abcfnrtv\\");
			if (tmp != arg[i + 1] || tmp == '\\')
				arg[i] = -1;
			else if (arg[i + 1] == 'c')
			{
				temp = arg;
				arg = ft_strsub(arg, 0, i);
				ft_strdel(&temp);
				break ;
			}
		}
	}
	e_interpretation_1(arg, flag);
}

/*
**	Builten echo
*/

void	built_echo(char **arg)
{
	int		flag;
	int		i;

	flag = 0;
	arg += (arg) ? 1 : 0;
	if (!((i = echo_options(arg, &flag)) == -1))
		arg += i;
	while (*(arg))
	{
		if (flag == n_flg && !*(arg + 1))
			n_flag(*arg, 1);
		else if (flag == e_flg)
			e_interpretation(*arg, 0);
		else if (flag == (e_flg | n_flg))
			e_interpretation(*arg, (!*(arg + 1)) ? 1 : 0);
		else
			ft_putstr_fd(*arg, 1);
		(*(arg + 1) != NULL) ? ft_putchar_fd(' ', 1) : 0;
		arg++;
	}
	if (flag != n_flg && (flag != ((e_flg | n_flg))))
		ft_putchar_fd('\n', 1);
	exit(EXIT_SUCCESS);
}
