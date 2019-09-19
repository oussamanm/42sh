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
** ft_lexer_quot : lexer for quote
*/

void		ft_lexer_quot(t_tokens **st_tokens, char *arg, int *j, int indx)
{
	int i;
	int quote;

	i = 0;
	quote = arg[0];
	while (arg[i] != '\0')
	{
		if (i != 0 && arg[i] == quote)
		{
			ft_fill_token(st_tokens, T_QUO, ft_strsub(arg, 0, i + 1), indx);
			*j += i;
			return ;
		}
		i++;
	}
}

/*
** ft_lexer_red : lexer for all redirection
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
		if (arg[i] == '&' && i != 2)
			str[k++] = '&';
		else if (arg[i] == '&')
			str[k++] = ERRO_IN_AND;
		else if ((arg[i] == '>' || arg[i] == '<') && (str[k++] = arg[i]))
		{
			if (arg[i + 1] && arg[i + 1] == arg[i])
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
** ft_lexer_txt : lexer for any txt
*/

void		ft_lexer_txt(t_tokens **st_tokens, char *arg, int *j, int indx)
{
	int		i;
	char	*temp;

	i = 0;
	while (arg[i] != '\0')
	{
		if (arg[i + 1] == ' ' || arg[i + 1] == '\t' || arg[i + 1] == '\0' ||
			arg[i + 1] == '&' || arg[i + 1] == '|' ||
				arg[i + 1] == '>' || arg[i + 1] == '<')
		{
			temp = ft_strsub(arg, 0, i + 1);
			ft_fill_token(st_tokens, T_TXT, temp, indx);
			break ;
		}
		i++;
	}
	*j += i;
}

/*
** ft_lexer_h : call funct lexer
*/

void		ft_lexer_h(t_tokens **st_tokens, char *arg, int i)
{
	int j;

	if (!arg)
		return ;
	j = 0;
	while (arg[j])
	{
		if (arg[j] == '"' || arg[j] == '\'')
			ft_lexer_quot(st_tokens, &arg[j], &j, i);
		else if (arg[j] == '&' && ft_check_char("><", arg[j + 1]))
			ft_lexer_red(st_tokens, &arg[j], &j, i);
		else if (arg[j] == '>' || arg[j] == '<')
			ft_lexer_red(st_tokens, &arg[j], &j, i);
		else if ((*st_tokens)->prev && (*st_tokens)->prev->token == T_RED_OUT_A
			&& arg[j] == '-' && j && arg[j - 1] == '&')
			ft_upd_token((*st_tokens)->prev, T_RED_OUT_B, ">&-");
		else
			ft_lexer_txt(st_tokens, &arg[j], &j, i);
		j++;
	}
}

/*
** ft_lexer : Lexer
*/

t_tokens	*ft_lexer(char **args)
{
	char		*arg;
	t_tokens	*st_tokens;
	t_tokens	*st_head;
	int			i;

	i = -1;
	st_tokens = ft_new_token();
	st_head = st_tokens;
	while (args[++i] != '\0')
	{
		arg = args[i];
		ft_lexer_h(&st_tokens, arg, i);
	}
	if (st_tokens != NULL && st_tokens->prev != NULL)
	{
		st_tokens->prev->next = NULL;
		free(st_tokens);
	}
	if (i == 0)
		return (NULL);
	return (st_head);
}
