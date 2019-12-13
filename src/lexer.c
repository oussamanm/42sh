/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhri <aboukhri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 23:39:18 by onouaman          #+#    #+#             */
/*   Updated: 2019/12/08 23:52:53 by aboukhri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "read_line.h"

/*
** Fill args with token except T_EQUAL
*/

void		tokens_to_args(t_pipes *st_pipe)
{
	t_tokens	*st_tokens;
	int			i;
	int			index;

	if (!st_pipe || !st_pipe->st_tokens)
		return ;
	i = 0;
	st_tokens = st_pipe->st_tokens;
	st_pipe->args = ft_strr_new(ft_count_tokens(st_pipe->st_tokens));
	index = st_tokens->indx;
	while (st_tokens)
	{
		if (st_tokens->is_arg != T_EQUAL)
		{
			if (i != 0 && index == st_tokens->indx)
				st_pipe->args[i - 1] = ft_strjoir_rtn(st_pipe->args[i - 1],\
						st_tokens->value, 1);
			else
			{
				st_pipe->args[i++] = ft_strdup(st_tokens->value);
				index = st_tokens->indx;
			}
		}
		st_tokens = st_tokens->next;
	}
}

/*
**  call functions for lexer
*/

void		args_to_token_h(t_tokens **st_tokens, char *arg, int *j, int i)
{
	if (arg[*j] == '\\')
		ft_lexer_txt(st_tokens, &arg[*j], j, i);
	else if (arg[*j] == ';')
		ft_fill_token(st_tokens, T_SEMICLN, ft_strdup(";"), i);
	else if (IS_QUOTE(arg[*j]))
		ft_lexer_quot(st_tokens, &arg[*j], j, i);
	else if (arg[*j] == '&' && M_CHECK(arg[*j + 1], '>', '<'))
		ft_lexer_red(st_tokens, &arg[*j], j, i);
	else if (M_CHECK(arg[*j], '>', '<') && arg[*j + 1] != '(')
		ft_lexer_red(st_tokens, &arg[*j], j, i);
	else if (CMP_TOKEN((*st_tokens)->prev, T_RED_OUT_A) && arg[*j] == '-')
		ft_upd_token((*st_tokens)->prev, T_RED_OUT_B, ">&-");
	else if (arg[*j] == '|' && arg[*j + 1] != '|')
		ft_fill_token(st_tokens, T_PIPE, ft_strdup("|"), i);
	else if (M_LOG_OPR(arg[*j], arg[*j + 1]))
		ft_lexer_logopr(st_tokens, &arg[*j], j, i);
	else if (arg[*j] == '&')
		ft_fill_token(st_tokens, T_JOBCTR, ft_strdup("&"), i);
	else if (arg[*j] == '=' && (*st_tokens)->prev &&
			(*st_tokens)->prev->token != T_EQUAL)
		ft_fill_token(st_tokens, T_EQUAL, ft_strdup("="), i);
	else if (M_SUBSH(arg[*j]) && arg[*j + 1] == '(')
		ft_lexer_subshl(st_tokens, &arg[*j], j, i);
	else
		ft_lexer_txt(st_tokens, &arg[*j], j, i);
}

/*
**  creation of tokens
*/

void		args_to_token(t_tokens **st_tokens, char *arg, int i)
{
	int	j;

	if (!arg)
		return ;
	j = -1;
	while (arg[++j])
		args_to_token_h(st_tokens, arg, &j, i);
}

/*
** Lexer
*/

t_tokens	*ft_lexer(char **args)
{
	t_tokens	*st_tokens;
	t_tokens	*st_head;
	int			i;

	i = 0;
	if (args == NULL)
		return (NULL);
	st_tokens = (ft_strrlen(args) > 0) ? ft_new_token() : NULL;
	st_head = st_tokens;
	while (args[i])
	{
		args_to_token(&st_tokens, args[i], i);
		i++;
	}
	if (st_tokens != NULL && PREV != NULL)
	{
		PREV->next = NULL;
		free(st_tokens);
	}
	return ((i != 0) ? st_head : NULL);
}
