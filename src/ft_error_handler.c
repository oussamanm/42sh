/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 16:38:33 by onouaman          #+#    #+#             */
/*   Updated: 2019/06/22 16:38:35 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		ft_err_exit(char *str)
{
	ft_putstr_fd(str, 2);
	exit(0);
}

/*
** ft_error_separ : Check error syntax (; and |) : O
** return 1 in case of error
*/

int			ft_error_separ(char *str_arg, char c)
{
	int		temp;
	char	**args;

	if ((args = ft_str_split_q(str_arg, " ;")) == NULL || *args == NULL)
	{
		ft_strrdel(args);
		return (1);
	}
	ft_strrdel(args);
	temp = 0;
	while (*str_arg)
	{
		if (*str_arg == c)
		{
			if (temp)
				return (1);
			str_arg++;
			temp = 1;
			continue ;
		}
		if (temp == 1 && *str_arg != ' ' && *str_arg != '\t')
			temp = 0;
		str_arg++;
	}
	return (0);
}

/*
** Check if exist error syntax of redirection
*/

int			ft_error_syn(t_pipes *st_pipes)
{
	if (st_pipes == NULL)
		return (0);
	while (st_pipes)
	{
		st_pipes->args = ft_str_split_q(st_pipes->cmd, " \t\n");
		st_pipes->st_tokens = ft_lexer(st_pipes->args);
		if (ft_error_redir(st_pipes->st_tokens))
		{
			ft_clear_cmds(st_pipes);
			return (1);
		}
		st_pipes = st_pipes->next;
	}
	return (0);
}

/*
** Check if exist error syntax of pipe
*/

int			ft_pipe_error(char *str)
{
	char	*tmp;
	int		i;

	i = 0;
	if (!str || (str && *str == 0))
		return (0);
	tmp = ft_strtrim(str);
	while (tmp && tmp[i])
	{
		if (tmp[i] == '|' && (i == 0 || tmp[i + 1] == '\0'))
			return (1);
		i++;
	}
	ft_strdel(&tmp);
	return (0);
}

int			ft_parse_error(char *str_cmds)
{
	if (str_cmds == NULL)
		return (1);
	if (ft_error_separ(str_cmds, '|') || ft_pipe_error(str_cmds))
	{
		ft_putstr_fd("syntax error near unexpected token `|' \n", 2);
		return (1);
	}
	return (0);
}
