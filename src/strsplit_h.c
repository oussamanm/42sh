/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strsplit_h.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 01:36:19 by onouaman          #+#    #+#             */
/*   Updated: 2019/10/11 01:36:21 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			find_dquot(char *str)
{
	int i; 
	
	i = 0;
	while (str[i])
	{
		if (M_ESCAPED(str[i]))
		{
			i += (str[i + 1]) ? 2 : 1;
			continue ;
		}
		if (str[i] == '(')
			i += find_subsh(&str[i]);
		else if (i && str[i] == '"')
			return (i);
		i++;
	}
	return (-1);
}

int			find_subsh(char *str)
{
	int i; 
	
	if (!str)
		return (-1);
	i = 0;
	while (str[i])
	{
		if (M_ESCAPED(str[i]))
		{
			i += (str[i + 1]) ? 2 : 1;
			continue ;
		}
		if (str[i] == '"')
			i += find_dquot(&str[i]);
		else if (str[i] == '\'')
			i += find_quot(&str[i]);
		else if (i && str[i] == '(')
			i += find_subsh(&str[i]);
		else if (str[i] == ')')
			return (i);
		i++;
	}
	return (-1);
}

int			find_quot(char *str)
{
	int i;

	if (!str)
		return (-1);
	i = 0;
	while (str[i])
	{
		if (i && str[i] == '\'')
			return (i);
		i++;
	}
	return (-1);
}

int			find_closed(char *str, char c)
{
	int i;

	i = 0;
	if (!str)
		return (-1);
	if (c == '"')
		i = find_dquot(str);
	else if (c == '\'')
		i = find_quot(str);
	else if (c == '(')
		i = find_subsh(str);
	return (i);
}