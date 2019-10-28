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
		if ((arg[i] == '|' && arg[i + 1] == '|') || (arg[i] == '&' && arg[i + 1] == '&'))
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
** ft_lexer_txt : lexer for any txt
*/

void		ft_lexer_txt(t_tokens **st_tokens, char *arg, int *j, int indx)
{
	int		i;
	int		escaped;
	char	*temp;

	i = 0;
	escaped = 0;
	while (arg[i] != '\0')
	{
		if (arg[i] == '\\' && !escaped)
		{
			i += (arg[i + 1]) ? 1 : 0;
			escaped = 1;
			continue ;
		}
		escaped = 0;
		if (arg[i + 1] == ' ' || arg[i + 1] == '\t' || arg[i + 1] == '\0' ||
			arg[i + 1] == '&' || arg[i + 1] == '|' ||
				arg[i + 1] == '>' || arg[i + 1] == '<' || (arg[0] != '=' && arg[i + 1] == '=') ||
				arg[i + 1] == '"' || arg[i + 1] == '\'')
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
**	Lexer sub_shell 
*/

void		ft_lexer_subshl(t_tokens **st_tokens, char *arg, int *j, int indx)
{
	int len;

	len = 0;
	if ((len = find_closed(&arg[1], '(')) != -1)
	{
		ft_fill_token(st_tokens, T_SUBSHL, ft_strsub(arg, 0, len + 2), indx);
		*j += (len + 1);
		return ;
	}
}


/*
**  call funct lexer
*/

void		ft_lexer_h(t_tokens **st_tokens, char *arg, int i)
{
	int j;

	if (!arg)
		return ;
	j = -1;
	while (arg[++j])
	{
				if (arg[j] == '\\')
				{
					//j += (arg[j + 1] && !M_SPEC_CHARC(arg[j + 1])) ? 1 : 0;
					ft_lexer_txt(st_tokens, &arg[j], &j, i);
				}
	/*Quot*/	else if (arg[j] == '"' || arg[j] == '\'')
					ft_lexer_quot(st_tokens, &arg[j], &j, i);
	/*Redi*/	else if (arg[j] == '&' && ft_check_char("><", arg[j + 1]))
					ft_lexer_red(st_tokens, &arg[j], &j, i);
				else if ((arg[j] == '>' || arg[j] == '<') && arg[j + 1] != '(')
					ft_lexer_red(st_tokens, &arg[j], &j, i);
				else if ((*st_tokens)->prev && (*st_tokens)->prev->token == T_RED_OUT_A
					&& arg[j] == '-' && j && arg[j - 1] == '&')
					ft_upd_token((*st_tokens)->prev, T_RED_OUT_B, ">&-");
	/*Pipe*/	else if (arg[j] == '|' && arg[j + 1] != '|')
					ft_fill_token(st_tokens, T_PIPE, ft_strdup("|"), i);
	/*Logi*/	else if ((arg[j] == '&' && arg[j + 1] == '&') || (arg[j] == '|' && arg[j + 1] == '|'))
					ft_lexer_logopr(st_tokens, &arg[j], &j, i);
	/*Jobs*/	else if (arg[j] == '&')
					ft_fill_token(st_tokens, '&', ft_strdup("&"), i);
				else if (arg[j] == '=' && (*st_tokens)->prev->token != T_EQUAL)
					ft_fill_token(st_tokens, '=', ft_strdup("="), i);
	/*SUB_SH*/	else if ((arg[j] == '$' || M_CHECK(arg[j], '>', '<')) && arg[j + 1] == '(')
					ft_lexer_subshl(st_tokens, &arg[j], &j, i);
	/*Txt*/		else
					ft_lexer_txt(st_tokens, &arg[j], &j, i);
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
	//printf("START \n");
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
	/*	st_tokens = st_head;
		while (st_tokens != NULL)
		{
			dprintf(2, "index = %d Token = <%d> : <%s>\n",st_tokens->indx, st_tokens->token,st_tokens->value);
			st_tokens = st_tokens->next;
		}
		dprintf(2,"\n--------------\n");
		//exit(0);*/
	if (i == -1)
		return (NULL);
	return (st_head);
}
