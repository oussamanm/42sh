/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 06:22:18 by onouaman          #+#    #+#             */
/*   Updated: 2019/05/03 06:23:35 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**	ft_str_split_q : Split with considering D/QUOT and SUB_SHELL
*/

char			**ft_str_split_q(char *str, char *c)
{
	int		i;
	char	**s_re;
	char	*temp;

	i = -1;
	if (!str || !c)
		return (NULL);
	temp = ft_strdup(str);
	while (temp[++i] != '\0')
	{
		if (temp[i] == '\\')
		{
			i += (temp[i + 1]) ? 1 : 0;
			continue ;
		}
		if (temp[i] == '(' || temp[i] == '"' || temp[i] == '\'')
			i += find_closed(&temp[i], temp[i]);
		if (ft_check_char(c, temp[i]))
			temp[i] = -1;
	}
	s_re = ft_strsplit(temp, -1);
	ft_strdel(&temp);
	return (s_re);
}

static int		ft_getlen(char const *str, char *c)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_check_char(c, str[i]) == 1)
			break ;
		i++;
	}
	return (i);
}

static int		ft_count_word(const char *str, char *c)
{
	int i;
	int rtn;
	int	i_bln;

	i = 0;
	i_bln = 0;
	rtn = (str && str[0] != '\0' && ft_check_char(c, str[0]) != 1) ? 1 : 0;
	while (str[i] != '\0')
	{
		if (ft_check_char(c, str[i]) == 1)
			i_bln = 1;
		else
		{
			if (i_bln == 1)
				rtn++;
			i_bln = 0;
		}
		i++;
	}
	return (rtn);
}

static int		ft_getindx(char const *str, char *c)
{
	int i;
	int i_bln;

	i = 0;
	i_bln = 0;
	while (str[i] != '\0')
	{
		if (ft_check_char(c, str[i]) != 1)
		{
			i_bln = 1;
			break ;
		}
		i++;
	}
	if (i_bln == 0)
		return (-1);
	else
		return (i);
}

char			**ft_str_split(char const *s, char *c)
{
	int		i;
	int		j;
	int		i_firstw;
	int		i_lenw;
	char	**s_re;

	i = 0;
	j = 0;
	if (s == NULL || c == NULL)
		return (NULL);
	if (!(s_re = (char **)malloc(sizeof(char *) * (ft_count_word(s, c) + 1))))
		return (NULL);
	while (s[i] != '\0')
	{
		i_firstw = ft_getindx(&s[i], c);
		if (i_firstw == -1)
			break ;
		i += i_firstw;
		i_lenw = ft_getlen(&s[i], c);
		s_re[j++] = ft_strsub(s, i, i_lenw);
		i += i_lenw;
	}
	s_re[j] = NULL;
	return (s_re);
}
