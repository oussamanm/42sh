/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_flag.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 12:04:41 by mfilahi           #+#    #+#             */
/*   Updated: 2019/12/21 12:04:46 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		alias_print_msg_error(char *s)
{
	print_error("invalid option", "alias: ", s, 0);
	print_error("alias [-p] [name[=value] ... ]", NULL, "alias: usage: ", 0);
}

t_tokens	*alias_options(t_tokens *curr, int *flag)
{
	int	i;

	while (curr)
	{
		if (curr->value[0] == '-')
		{
			i = 0;
			while (curr->value[++i])
			{
				if (curr->value[i] == 'p')
					*flag = 2;
				else if ((*flag = 1))
				{
					alias_print_msg_error(curr->value);
					return (curr);
				}
			}
			if (curr->value[0] == '-' && !curr->value[1])
				return (curr);
		}
		else
			break ;
		curr = curr->next;
	}
	return (curr);
}

int			error_checker(char *str, int flag)
{
	int i;

	if (!str)
		return (0);
	if (str[0] == '-')
	{
		(flag) ? alias_print_msg_error(str) : 0;
		return (0);
	}
	if (str[0] == '=')
	{
		(flag) ? print_error(": not found", "alias: ", str, 0) : 0;
		return (0);
	}
	i = -1;
	while (str[++i])
	{
		if (str[i] == '/')
		{
			(flag) ? print_error(": invalid alias name", "alias: ", str, 0) : 0;
			return (0);
		}
	}
	return (1);
}

char		*remove_quotes(char *str)
{
	int		i;
	int		j;
	char	*newstr;

	i = -1;
	while (str[++i])
		if (str[i] == '\'' || str[i] == '"')
			str[i] = -1;
	j = 0;
	i = -1;
	while (str[++i])
		if (str[i] != -1)
			j++;
	newstr = ft_strnew(j);
	j = 0;
	i = -1;
	while (str[++i])
	{
		if ((str[i] != -1))
			newstr[j++] = str[i];
	}
	newstr[j] = '\0';
	return (newstr);
}

void		importaliasfilecontent_2(char *nline)
{
	int		i;
	char	*str1;
	char	*str2;

	i = 0;
	while (nline[i] && nline[i] != '=')
		i++;
	str1 = ft_strsub(nline, 0, i);
	str2 = ft_strsub(nline, ++i, ft_strlen(nline));
	(nline) ? ft_strdel(&nline) : 0;
	if (!error_checker(str1, 0))
	{
		ft_strdel(&str1);
		ft_strdel(&str2);
		return ;
	}
	rm_alias_by_elem_flag(str1);
	if (!str2)
		str2 = ft_strdup("");
	pushtolist(str1, str2, 1);
	ft_strdel(&str1);
	ft_strdel(&str2);
}
