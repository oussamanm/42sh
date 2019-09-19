/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_q.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 05:28:59 by onouaman          #+#    #+#             */
/*   Updated: 2019/08/07 05:29:02 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**	ft_str_split_q : Split with quoting :
*/

char		**ft_str_split_q(char *str, char *c)
{
	int		i;
	char	**s_re;
	char	save;
	char	*temp;

	i = 0;
	if (str == NULL || c == NULL)
		return (NULL);
	temp = ft_strdup(str);
	save = 0;
	while (temp[i] != '\0')
	{
		if (save == 0 && (temp[i] == '"' || temp[i] == '\''))
			save = temp[i];
		else if (temp[i] == save)
			save = 0;
		if (save == 0 && ft_check_char(c, temp[i]))
			temp[i] = -1;
		i++;
	}
	s_re = ft_strsplit(temp, -1);
	ft_strdel(&temp);
	return (s_re);
}

/*
**	ft_index_of_first_split : Splite string with string :
*/

int			ft_index_of_first_split(char *s1, char *s2)
{
	int i;
	int quote;
	int j;

	if (!s2[0])
		return (-1);
	i = -1;
	quote = 0;
	while (s1[++i])
	{
		j = 0;
		if (quote == 0 && (s1[i] == '\'' || s1[i] == '"'))
			quote = s1[i];
		else if (s1[i] == quote)
			quote = 0;
		while (!quote && s1[i + j] == s2[j])
		{
			if (s2[j + 1] == '\0')
				return (i);
			j++;
		}
	}
	return (-1);
}

char		**ft_strsplit_by_arr(char *str, char *split)
{
	int		i;
	int		j;
	char	*tmp;
	char	**resu;

	resu = NULL;
	tmp = ft_strdup(str);
	while ((i = ft_index_of_first_split(tmp, split)) != -1)
	{
		j = -1;
		while (split[++j] && split[j] == tmp[i])
			tmp[i++] = -1;
	}
	resu = ft_strsplit(tmp, -1);
	ft_strdel(&tmp);
	return (resu);
}
