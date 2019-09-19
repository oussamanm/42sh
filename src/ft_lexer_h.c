/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_h.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 02:18:45 by onouaman          #+#    #+#             */
/*   Updated: 2019/08/06 02:18:46 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Calculate sum of ASCI :
*/

int			ft_sum_asci(char str[])
{
	int	sum;

	if (str == NULL)
		return (0);
	sum = 0;
	while (*str != '\0')
	{
		sum += *str;
		str++;
	}
	return (sum);
}

/*
** Fill t_tokens :
*/

void		ft_fill_token(t_tokens **st_tokens, int token,
	char *value, int indx)
{
	t_tokens	*prev;

	(*st_tokens)->token = token;
	(*st_tokens)->value = value;
	(*st_tokens)->indx = indx;
	(*st_tokens)->next = ft_new_token();
	prev = (*st_tokens);
	(*st_tokens) = (*st_tokens)->next;
	(*st_tokens)->prev = prev;
}

/*
** ft_upd_token : append - to redirection if separated :
*/

void		ft_upd_token(t_tokens *st_tokens, int token, char *value)
{
	if (st_tokens == NULL)
		return ;
	st_tokens->token = token;
	if (st_tokens->value != NULL)
		ft_strdel(&(st_tokens->value));
	st_tokens->value = ft_strdup(value);
}
