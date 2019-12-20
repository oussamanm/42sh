/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_call.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 18:37:39 by onouaman          #+#    #+#             */
/*   Updated: 2019/12/02 06:38:33 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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
	else
		ft_lexer_txt(st_tokens, arg, j, indx);
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
		if (arg[i] == '&' && i < 2)
			str[k++] = '&';
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
		escaped = (arg[i] == '\\' && !escaped) ? 1 : 0;
		if (!arg[i + 1] || M_CHECK(arg[i + 1], ' ', '\t') ||
			M_CHECK(arg[i + 1], '&', '|') || IS_QUOTE(arg[i + 1]) ||
			(M_SUBSH(arg[i + 1]) && arg[i + 2] == '(') || M_REDIR(arg[i + 1]) ||
			(arg[0] != '=' && arg[i + 1] == '=') || arg[i + 1] == ';')
		{
			if (escaped && arg[i + 1])
				continue ;
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
	else
		ft_lexer_txt(st_tokens, arg, j, indx);
}
