/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 23:39:18 by onouaman          #+#    #+#             */
/*   Updated: 2019/07/24 23:39:19 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "read_line.h"

/*
** lexer for quote
*/

void		ft_lexer_quot(t_tokens **st_tokens, char *arg, int *j, int indx)
{
	int i;
	int token;
	int len;

	i = 0;
	len = 0;
	if ((len = find_closed(arg, arg[0])) != -1)
	{
		token = (arg[0] == '"') ? T_DQUO : T_QUO;
		ft_fill_token(st_tokens, token, ft_strsub(arg, 0, len + 1), indx);
		*j += len;
		return ;
	}
}

/*
** lexer for all redirection
*/

void		ft_lexer_red(t_tokens **st_tokens, char *arg, int *j, int indx)
{
	int		i;
	int		k;
	char	str[5];

	i = -1;
	k = 0;
	ft_bzero(str, 5);
	while (arg[++i] != '\0')
	{
		if (arg[i] == '&')
			str[k++] = '&';
		else if (arg[i] == '&' && i > 2)
			str[k++] = ERRO_IN_AND;
		else if ((arg[i] == '>' || arg[i] == '<') && (str[k++] = arg[i]))
		{
			if (arg[i + 1] == arg[i])
				str[k++] = arg[++i];
		}
		else if (arg[i] == '-' && k == 2 && str[1] == '&')
			str[k++] = '-';
		else
			break ;
	}
	ft_fill_token(st_tokens, ft_sum_asci(str) * -1, ft_strdup(str), indx);
	*j += (i <= 0) ? 0 : (i - 1);
}

/*
** lexer for || &&
*/

void		ft_lexer_logopr(t_tokens **st_tokens, char *arg, int *j, int indx)
{
	int		i;
	char	*temp;

	i = 0;
	temp = NULL;
	while (arg[i])
	{
		if ((arg[i] == '|' && arg[i + 1] == '|')
			|| (arg[i] == '&' && arg[i + 1] == '&'))
		{
			temp = (arg[i] == '|') ? ft_strdup("||") : ft_strdup("&&");
			i++;
			break ;
		}
		i++;
	}
	ft_fill_token(st_tokens, ft_sum_asci(temp), temp, indx);
	*j += i;
}

/*
** lexer for txt
*/

void		ft_lexer_txt(t_tokens **st_tokens, char *arg, int *j, int indx)
{
	int		i;
	int		escaped;
	char	*temp;

	i = -1;
	escaped = 0;
	while (arg[++i] != '\0')
	{
		if (arg[i] == '\\' && !escaped)
		{
			i += (arg[i + 1]) ? 1 : 0;
			escaped = 1;
			continue ;
		}
		escaped = 0;
		if (arg[i + 1] == ' ' || arg[i + 1] == '\t' || !arg[i + 1] || M_BRACKET(arg[i + 1]) ||
			arg[i + 1] == '&' || arg[i + 1] == '|' || M_REDIR(arg[i + 1]) ||
			arg[i + 1] == '$' || (arg[0] != '=' && arg[i + 1] == '=') || IS_QUOTE(arg[i + 1]))
		{
			temp = ft_strsub(arg, 0, i + 1);
			ft_fill_token(st_tokens, T_TXT, temp, indx);
			break ;
		}
	}
	*j += i;
}

/*
**	Lexer sub_shell
*/

void		ft_lexer_subshl(t_tokens **st_tokens, char *arg, int *j, int indx)
{
	int	len;
	int	token;

	len = 0;
	if (arg[0] == '$')
		token = T_SUBSHL;
	else
		token = (arg[0] == '<') ? T_PROC_IN : T_PROC_OUT;
	if ((len = find_closed(&arg[1], '(')) != -1)
	{
		ft_fill_token(st_tokens, token, ft_strsub(arg, 0, len + 2), indx);
		*j += (len + 1);
		return ;
	}
}

/*
**  call functions for lexer
*/

void		ft_lexer_h(t_tokens **st_tokens, char *arg, int i)
{
	int j;

	if (!arg)
		return ;
	j = -1;
	while (arg[++j])
	{
	/*Esca_ch*/	if (arg[j] == '\\')
					ft_lexer_txt(st_tokens, &arg[j], &j, i);
	/*Quot*/	else if (IS_QUOTE(arg[j]))
					ft_lexer_quot(st_tokens, &arg[j], &j, i);
	/*Redi*/	else if (arg[j] == '&' && M_CHECK(arg[j + 1], '>', '<'))
					ft_lexer_red(st_tokens, &arg[j], &j, i);
				else if (M_CHECK(arg[j], '>', '<') && arg[j + 1] != '(')
					ft_lexer_red(st_tokens, &arg[j], &j, i);
				else if ((*st_tokens)->prev && (*st_tokens)->prev->token == T_RED_OUT_A
					&& arg[j] == '-' && j && arg[j - 1] == '&')
					ft_upd_token((*st_tokens)->prev, T_RED_OUT_B, ">&-");
	/*Brack*/	else if (M_BRACKET(arg[j]))
					ft_fill_token(st_tokens, arg[j], ft_strdup((char [2]){arg[j], '\0'}), i);
	/*Pipe*/	else if (arg[j] == '|' && arg[j + 1] != '|')
					ft_fill_token(st_tokens, T_PIPE, ft_strdup("|"), i);
	/*Logi*/	else if ((arg[j] == '&' && arg[j + 1] == '&') || (arg[j] == '|' && arg[j + 1] == '|'))
					ft_lexer_logopr(st_tokens, &arg[j], &j, i);
	/*Jobs*/	else if (arg[j] == '&')
					ft_fill_token(st_tokens, T_JOBCTR, ft_strdup("&"), i);
				else if (arg[j] == '=' && (*st_tokens)->prev && (*st_tokens)->prev->token != T_EQUAL)
					ft_fill_token(st_tokens, T_EQUAL, ft_strdup("="), i);
	/*SUB_SH*/	else if ((arg[j] == '$' || M_CHECK(arg[j], '>', '<')) && arg[j + 1] == '(')
					ft_lexer_subshl(st_tokens, &arg[j], &j, i);
	/*Txt*/		else
					ft_lexer_txt(st_tokens, &arg[j], &j, i);
	}
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
	while (args[i] != '\0')
	{
		ft_lexer_h(&st_tokens, args[i], i);
		i++;
	}
	if (st_tokens != NULL && st_tokens->prev != NULL)
	{
		st_tokens->prev->next = NULL;
		free(st_tokens);
	}
		// st_tokens = st_head;
		// while (st_tokens != NULL)
		// {
		// 	dprintf(2, "index = %d Token = <%d> : <%s>\n",st_tokens->indx, st_tokens->token,st_tokens->value);
		// 	st_tokens = st_tokens->next;
		// }
		// dprintf(2,"\n--------------\n");
		// exit(0);
	if (i == 0)
		return (NULL);
	return (st_head);
}
