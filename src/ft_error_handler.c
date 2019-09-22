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

/*
** Check error syntax of command ; | 
*/

char		**ft_error_syntax(char *str_cmds)
{
	char	**args;
	int		i;

	i = 0;
	if (ft_error_separ(str_cmds, ';'))
	{
		ft_putstr_fd("syntax error near unexpected token `;' \n", 2);
		ft_strdel(&str_cmds);
		return (NULL);
	}
	if ((args = ft_str_split_q(str_cmds, ";")) == NULL || *args == NULL)
	{
		ft_putstr_fd("syntax error near unexpected tokenl `;' \n", 2);
		ft_strrdel(args);
		ft_strdel(&str_cmds);
		return (NULL);
	}
	return (args);
}

/*
** Check error syntax (; and |)
** 		return 1 in case of error
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
** Check error syntax of pipe |
*/

int			ft_error_pipe(char *str)
{
	char	*tmp;
	int		i;

	i = 0;
	if (!str || (str && *str == 0))
		return (0);
	if (ft_error_separ(str, '|'))
	{
		ft_putstr_fd("syntax error near unexpected token `|' \n", 2);
		return (1);
	}
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

/*
** ft_error_redir_h: helper funct for ft_error_redir :
*/

int			ft_error_redir_h(t_tokens *st_tokens)
{
	if (st_tokens->token == T_RED_APP_S && NEXT && NEXT->token == T_TXT)
		if (NEXT->indx != st_tokens->indx &&
			NEXT->next && NEXT->next->token < 0)
			return (ft_putendl_fd("syntax error near unexpected token ", 2));
	if (st_tokens->token < T_RED_APP_M)
		return (ft_putendl_fd("syntax error near unexpected token ", 2));
	if (st_tokens->token <= -122 && !ft_strncmp(st_tokens->value, "><", 2))
		return (ft_putendl_fd("syntax error near unexpected token `<'", 2));
	return (0);
}

/*
** ft_error_redir: Check Error syntax of redirection
*/

int			ft_error_redir(t_tokens *st_tokens)
{
	while (st_tokens != NULL)
	{
		if (st_tokens->token == T_RED_OUT_S && NEXT && NEXT->token == T_TXT &&
			NEXT->value && NEXT->value[0] == '&')
			return (ft_putendl_fd("syntax error near unexpected token `&'", 2));
		if (ft_error_redir_h(st_tokens))
			return (1);
		if (st_tokens->token < 0 &&
			ft_check_char(st_tokens->value, ERRO_IN_AND))
			return (ft_putendl_fd("syntax error near unexpected token `&'", 2));
		if (st_tokens->token < 0 && (NEXT == NULL || NEXT->token < 0) &&
			st_tokens->token != -145 && st_tokens->token != -143)
			return (ft_putendl_fd("syntax error near unexpected token", 2));
		if (st_tokens->token == T_RED_OUT_A && NEXT &&
			!ft_isalldigit(NEXT->value) && PREV && PREV->indx == st_tokens->indx
			&& ft_isalldigit(PREV->value) && ft_atoi(PREV->value) != 1)
			return (ft_putendl_fd("ambiguous redirect", 2));
		if ((st_tokens->token == T_RED_OUT_A || st_tokens->token == T_RED_HER_D)
			&& NEXT && NEXT->value && NEXT->value[0] == '&')
			return (ft_putendl_fd("syntax error near unexpected token `&'", 2));
		st_tokens = NEXT;
	}
	return (0);
}
