/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhri <aboukhri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 05:43:45 by aboukhri          #+#    #+#             */
/*   Updated: 2019/12/08 06:22:32 by aboukhri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_line.h"

static	int		exp_error(char c)
{
	char *msg;

	msg = (c == 0) ? "newline" : (char[2]){c, '\0'};
	ft_putstr_fd("42sh: syntax error near unexpected token `", 2);
	ft_putstr_fd(msg, 2);
	ft_putendl_fd("'", 2);
	return (0);
}

int				is_expansion_syntax(char *cmd)
{
	int	i;
	int	bl;
	int	q;

	i = -1;
	bl = 0;
	q = 0;
	while (cmd[++i])
	{
		if (cmd[i] == '\'')
			q = (!q) ? 1 : 0;
		if (!q && (M_CHECK(cmd[i], '|', ';') || M_CHECK(cmd[i], '&', '!')))
		{
			if (bl == 1)
				return (exp_error(cmd[i]));
			if (cmd[i] != '!')
				bl = 0;
			else if (bl != -1)
				bl = 1;
		}
		else if (ft_isprint(cmd[i]) && cmd[i] != ' ')
			bl = -1;
	}
	return ((bl == 1) ? exp_error(0) : 1);
}

char			*shift_expansion(char *keyword, int *i)
{
	int	bg;

	bg = *i;
	while (keyword[*i] && keyword[*i] != '"'
			&& !is_shell_delimiter(keyword[*i]) && !ft_isspace(keyword[*i]))
		*i += 1;
	return (ft_strsub(keyword, bg, *i - bg));
}
