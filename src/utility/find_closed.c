/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_closed.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhri <aboukhri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 12:30:19 by onouaman          #+#    #+#             */
/*   Updated: 2019/12/01 20:46:55 by aboukhri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			find_dquot(char *str)
{
	int i;
	int j;
	
	i = 0;
	j = 0;
	while (str[i])
	{
		if (M_ESCAPED(str[i]))
		{
			i += (str[i + 1]) ? 2 : 1;
			continue ;
		}
		if (str[i] == '(')
		{
			if ((j = find_subsh(&str[i])) != -1)
				i += j;
		}
		else if (i && str[i] == '"')
			return (i);
		i++;
	}
	return (-1);
}

int			find_subsh(char *str)
{
	int i;
	int temp;
	
	if (!str)
		return (-1);
	i = 0;
	temp = 0;
	while (str[i] && temp != -1)
	{
		temp = 0;
		if (M_ESCAPED(str[i]))
		{
			i += (str[i + 1]) ? 2 : 1;
			continue ;
		}
		if (str[i] == '"' && (temp = find_dquot(&str[i])) != -1)
			i += temp;
		else if (str[i] == '\'' && (temp = find_quot(&str[i])) != -1)
			i += temp;
		else if (i && str[i] == '(' && (temp = find_subsh(&str[i])) != -1)
			i += temp;
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
