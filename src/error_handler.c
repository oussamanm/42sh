/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 16:38:33 by onouaman          #+#    #+#             */
/*   Updated: 2019/12/02 06:44:57 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** helper function for error_syntax_lexer
*/

int			syntax_error_h(t_tokens *st_tokens)
{
	int	bl;

	bl = 0;
	if (st_tokens->token == T_PIPE &&
		(!PREV || !NEXT || OPER_TOKEN(NEXT->token)))
		bl = 1;
	else if (st_tokens->token == T_JOBCTR &&
		(!PREV || (NEXT && OPER_TOKEN(NEXT->token))))
		bl = 1;
	else if (st_tokens->token == T_LOGOPR_AND &&
		(!PREV || !NEXT || OPER_TOKEN(NEXT->token)))
		bl = 1;
	else if (st_tokens->token == T_LOGOPR_OR &&
		(!PREV || !NEXT || OPER_TOKEN(NEXT->token)))
		bl = 1;
	return (bl);
}

/*
** Check errors Syntax (Lexer) resirection, pipe, job_ctr, || , &&
*/

int			error_syntax_lexer(t_tokens *st_tokens)
{
	char	*tmp;
	int		bl;

	tmp = NULL;
	bl = 0;
	if (!st_tokens)
		return (0);
	while (st_tokens && !bl)
	{
		bl = syntax_error_h(st_tokens);
		if (bl && (!PREV || !NEXT))
			tmp = ft_strdup(st_tokens->value);
		else if (bl && NEXT)
			tmp = ft_strdup(NEXT->value);
		st_tokens = st_tokens->next;
	}
	if (!bl)
		return (0);
	print_error(tmp, NULL, ERR_SYN, 0);
	free(tmp);
	return (1);
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
** Helper for handle error redirection
*/

char		*error_redir_h(t_tokens *st_tokens)
{
	char	*temp;
	char	*msg;

	msg = NULL;
	temp = NULL;
	if (TOKEN < 0 && ((!NEXT && !M_CHECK(TOKEN, T_RED_IN_B, T_RED_OUT_B)) ||
		(NEXT && !T_IS_TXT(NEXT->token) && !T_IS_SUBSHELL(NEXT->token))))
		msg = "syntax error near unexpected token";
	else if (TOKEN < T_RED_APP_A)
		msg = "syntax error near unexpected token";
	else if (TOKEN < 0 && ft_check_char(st_tokens->value, ERRO_IN_AND))
		msg = "syntax error near unexpected token `&'";
	else if (TOKEN == T_RED_OUT_A && *(st_tokens->value) == '>' &&
			NEXT && !ft_isalldigit(NEXT->value) &&
			PREV && PREV->indx == st_tokens->indx &&
			ft_isalldigit(PREV->value) && ft_atoi(PREV->value) != 1)
		msg = "ambiguous redirect";
	else if (TOKEN == T_RED_IN_A && NEXT &&
			!ft_isalldigit((temp = get_value_next(NEXT))))
		msg = "ambiguous redirect ";
	else if (TOKEN <= -122 && !ft_strncmp(st_tokens->value, "><", 2))
		msg = "syntax error near unexpected token `<'";
	free(temp);
	return (ft_strdup(msg));
}

/*
** Check Error syntax of redirection
*/

int			error_redir(t_tokens *st_tokens)
{
	char	*msg_err;

	msg_err = NULL;
	while (st_tokens != NULL)
	{
		if ((msg_err = error_redir_h(st_tokens)))
		{
			print_error(msg_err, NULL, NULL, 0);
			ft_strdel(&msg_err);
			return (1);
		}
		st_tokens = NEXT;
	}
	ft_strdel(&msg_err);
	return (0);
}
