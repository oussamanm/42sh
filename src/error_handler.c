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
		if (st_tokens->token == T_PIPE && (!PREV || !NEXT || NEXT->token == T_PIPE))
			ft_strcpy(tmp, "|");
		else if (st_tokens->token == T_JOBCTR && (!PREV || (NEXT && NEXT->token == T_JOBCTR)))
			ft_strcpy(tmp, "&");
		else if (st_tokens->token == T_LOGOPR_AND && (!PREV || !NEXT || NEXT->token == T_LOGOPR_AND))
			ft_strcpy(tmp, "&&");
		else if (st_tokens->token == T_LOGOPR_OR && (!PREV || !NEXT || NEXT->token == T_LOGOPR_OR))
			ft_strcpy(tmp, "||");
		else if (M_BRACKET(st_tokens->token))
			tmp[0] = st_tokens->token;
		if (tmp[0] != 0)
			break ;
		st_tokens = st_tokens->next;
	}
	if (tmp[0] == 0)
		return (0);
	print_error(tmp, NULL, "syntax error near unexpected token", 0);
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
	if (!args || (ft_strrlen(args) > 1 && (!(*args) || (*args)[0] == '\0')))
	{
		print_error("syntax error near unexpected token `;'", NULL, NULL, 0);
		return (1);
	}
	while (str_cmds[++i])
	{
		if (str_cmds[i] == ';')
		{
			if (temp || str_cmds[0] == ';')
			{
				print_error("syntax error near unexpected token `;'", NULL, NULL, 0);
				return (1);
			}
			temp = 1;
			continue ;
		}
		if (temp && !ft_isspace(str_cmds[i]))
			temp = 0;
	}
	return (0);
}

/*
** Check error syntax of expansion ${} 
*/

int			error_syntax_expans(char *str_cmds)
{
	int bl;
	int i;

	if (!str_cmds)
		return (0);
	bl = 0;
	i = 0;
	while (str_cmds[i])
	{
		if (!bl && str_cmds[i] == '$' && str_cmds[i + 1] == '{' && ++i)
			bl = 1;
		else if (bl)
		{
			if (str_cmds[i] == '}' && bl)
				bl = 0;
			else if (!ft_isalphanum(str_cmds[i]))
			{
				print_error(" bad substitution", NULL, NULL, 0);
				return (1);
			}
		}
		i += (str_cmds[i] != '\0');
	}
	return (0);
}


/*
** Check Error syntax of redirection
*/

int			ft_error_redir(t_tokens *st_tokens)
{
	char msg_err[50];

	ft_bzero(msg_err, 50);
	while (st_tokens != NULL)
	{
		/// check  case redirection followed by NULL or a token not TXT
		if (st_tokens->token < 0 && (NEXT == NULL || NEXT->token != T_TXT))
			ft_strcpy(msg_err, "syntax error near unexpected token");
		/// check token not exist
		else if (st_tokens->token < T_RED_APP_A)
			ft_strcpy(msg_err, "syntax error near unexpected token");
		/// check unexpected & in redirection
		else if (st_tokens->token < 0 && ft_check_char(st_tokens->value, ERRO_IN_AND))
			ft_strcpy(msg_err, "syntax error near unexpected token `&'");
		/// check  case "echo hello 3>&file" => "ambiguous redirect"
		else if (st_tokens->token == T_RED_OUT_A && NEXT && PREV &&
			!ft_isalldigit(NEXT->value) && PREV->indx == st_tokens->indx &&
			ft_isalldigit(PREV->value) && ft_atoi(PREV->value) != 1)
			ft_strcpy(msg_err, "ambiguous redirect");
		/// check case token >< 
		else if (st_tokens->token <= -122 && !ft_strncmp(st_tokens->value, "><", 2))
			ft_strcpy(msg_err, "syntax error near unexpected token `<'");
		st_tokens = NEXT;
	}
	if (msg_err[0] != 0)
	{
		print_error(msg_err, NULL, NULL, 0);
		return (1);
	}
	return (0);
}