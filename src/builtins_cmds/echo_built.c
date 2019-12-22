/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_built.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhri <aboukhri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 12:17:27 by mfilahi           #+#    #+#             */
/*   Updated: 2019/12/02 02:38:07 by aboukhri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "read_line.h"

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

int		e_interpretation(char *arg, t_tokens **st, int i, char *str)
{
	char	tmp;
	char	*temp;

	temp = ft_strdup(arg);
	while (temp[++i])
	{
		if (temp[i] != '\\')
			continue ;
		tmp = temp[i + 1];
		temp[i + 1] = echo_charcmp(temp[i + 1], "abcfnrtv\\");
		if (tmp != temp[i + 1] || tmp == '\\')
			temp[i++] = -1;
		else if (temp[i + 1] == 'c')
		{
			str = temp;
			temp = ft_strsub(temp, 0, i);
			ft_strdel(&str);
			*st = NULL;
			break ;
		}
	}
	return ((e_interpretation_1(temp) == -1) ? 1 : 0);
}

/*
** verified options of echo;
*/

int		echo_options(t_tokens **st_tokens)
{
	int		i;
	int		flag;
	char	*arg;

	i = 0;
	flag = 0;
	while (*st_tokens)
	{
		arg = (*st_tokens)->value;
		if (arg && arg[0] == '-' &&\
		(M_CHECK(arg[1], 'n', 'e') || arg[1] == 'E'))
			echo_options_(&arg[1], &flag);
		else
			break ;
		*st_tokens = (*st_tokens)->next;
	}
	return (flag);
}

int		hendl_echo(int flag, t_tokens **st_tokens, int *index)
{
	int		status;
	char	*tmp;

	if (M_CHECK(flag, (e_flg | n_flg), e_flg))
	{
		tmp = get_value_next(*st_tokens);
		status = e_interpretation(tmp, st_tokens, -1, NULL);
		ft_strdel(&tmp);
		if (M_CHECK(flag, (e_flg | n_flg), n_flg))
			n_flag("");
		return (status);
	}
	else
		status = (ft_putstr((*st_tokens)->value) == -1) ? 1 : 0;
	if (M_CHECK(flag, (e_flg | n_flg), n_flg) && !(*st_tokens)->next)
		n_flag((*st_tokens)->value);
	if ((*st_tokens)->next && (*st_tokens)->next->indx != *index &&\
		(*index = (*st_tokens)->next->indx))
		ft_putchar_fd(' ', 1);
	return (status);
}

/*
**	Builten echo
*/

int		built_echo(t_tokens *st_tokens)
{
	int		flag;
	int		index;
	int		status;

	st_tokens = NEXT;
	status = 0;
	flag = echo_options(&st_tokens);
	index = (st_tokens) ? st_tokens->indx : 1;
	while (st_tokens && !status)
	{
		if (TOKEN_IS_ARG(st_tokens))
			status = hendl_echo(flag, &st_tokens, &index);
		else
			index = (NEXT) ? NEXT->indx : index;
		st_tokens = (st_tokens) ? NEXT : NULL;
	}
	(flag != n_flg && flag != ((e_flg | n_flg))) && (my_outc('\n'));
	return (status);
}
