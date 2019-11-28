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
** this functinon serve option echo -n;
*/

void	n_flag(char *arg)
{
	if (!arg)
		return ;
	if (arg[ft_strlen(arg) - 1] != '\n')
	{
		ft_putstr("\033[7m");
		ft_putchar('%');
		ft_putstr("\033[m\n");
	}
}

/*
** this functinon serve option echo -e;
*/

void	e_interpretation(char *arg)
{
	char	tmp;
	char	*temp;
	int		i;

	i = -1;
	while (arg[++i])
	{
		if (arg[i] != '\\')
			continue ;
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
	e_interpretation_1(arg);
}

/*
** - verified options of echo;
*/

int		echo_options(t_tokens **st_tokens)
{
	int i;
	int flag;
	char *arg;

	i = 0;
	flag = 0;
	while (*st_tokens)
	{
		arg = (*st_tokens)->value;
		if (arg && arg[0] == '-' && (M_CHECK(arg[1], 'n', 'e') || arg[1] == 'E'))
			echo_options_(&arg[1], &flag);
		else
			break ;
		*st_tokens = (*st_tokens)->next;
	}
	return (flag);
}


/*
**	Builten echo
*/

void	built_echo(t_tokens *st_tokens)
{
	int		flag;
	int		index;

	if (!st_tokens)
		return ;
	st_tokens = NEXT;
	flag = echo_options(&st_tokens);
	index = (st_tokens) ? st_tokens->indx : 1;
	while (st_tokens)
	{
		if (M_CHECK(flag, (e_flg | n_flg), e_flg) && M_CHECK(st_tokens->token, T_QUO, T_DQUO))
			e_interpretation(st_tokens->value);
		else
			ft_putstr(st_tokens->value);
		if (M_CHECK(flag, (e_flg | n_flg), n_flg) && !NEXT)
			n_flag(st_tokens->value);
		if (NEXT && NEXT->indx != index)
		{
			ft_putchar_fd(' ', 1);
			index = NEXT->indx;
		}
		st_tokens = NEXT;
	}
	if (flag != n_flg && flag != ((e_flg | n_flg)))
		ft_putchar_fd('\n', 1);
}
