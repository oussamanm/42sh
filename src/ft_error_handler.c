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
** Check errors Syntax (Lexer) resirection, pipe, job_ctr, || , &&
*/

int			error_syntax_lexer(t_tokens *st_tokens)
{
	char tmp[3];

	ft_bzero(tmp, 3);
	if (!st_tokens)
		return (0);
	if (ft_error_redir(st_tokens))
		return (1);
	while (st_tokens)
	{
		if (st_tokens->token == T_PIPE && ((!PREV || !NEXT) || NEXT->token == T_PIPE))
			ft_strcpy(tmp, "|");
		else if (st_tokens->token == T_JOBCTR && (!PREV || (NEXT && NEXT->token == T_JOBCTR)))
			ft_strcpy(tmp, "&");
		else if (st_tokens->token == T_LOGOPR_AND && ((!PREV || !NEXT) || NEXT->token == T_LOGOPR_AND))
			ft_strcpy(tmp, "&&");
		else if (st_tokens->token == T_LOGOPR_OR && ((!PREV || !NEXT) || NEXT->token == T_LOGOPR_OR))
			ft_strcpy(tmp, "||");
		if (tmp[0] != 0)
			break ;
		st_tokens = st_tokens->next;
	}
	if (tmp[0] == 0)
		return (0);
	ft_print_error(tmp, "42sh: ", "syntax error near unexpected token", 0);
	return (1);
}

/*
** Check error syntax of command ;
*/

int			error_syntax_semi(char *str_cmds, char **args)
{
	int		temp;
	int		i;

	temp = 0;
	i = -1;
	if (!args || !*args)
	{
		ft_putstr_fd("syntax error near unexpected tokenl `;' \n", 2);
		return (1);
	}
	while (str_cmds[++i])
	{
		if (str_cmds[i] == ';')
		{
			if (temp || str_cmds[0] == ';')
			{
				ft_putstr_fd("syntax error near unexpected token `;' \n", 2);
				return (1);
			}
			i++;
			temp = 1;
			continue ;
		}
		if (temp && !ft_isspace(str_cmds[i]))
			temp = 0;
	}
	return (0);
}

/*
** Check error syntax of sub_shell $() , <() >() 
*/

int			error_syntax_expans(char *str_cmds)
{
	int bl;
	int i;

	if (!str_cmds)
		return (0);
	bl = 0;
	i = -1;
	while (str_cmds[++i])
	{
		if (!bl && str_cmds[i] == '$' && str_cmds[i + 1] == '{' && ++i)
			bl = 1;
		else if (bl)
		{
			if (str_cmds[i] == '}' && bl)
				bl = 0;
			else if (!ft_isalphanum(str_cmds[i]))
			{
				ft_print_error("bad substitution", "42sh :", NULL, 0);
				return (1);
			}
		}
	}
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
