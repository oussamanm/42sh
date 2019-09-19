/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 22:45:55 by onouaman          #+#    #+#             */
/*   Updated: 2018/10/21 01:56:47 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_compte(const char *s, char c)
{
	int i;
	int j;

	j = 0;
	i = 0;
	if (s[0] != c)
		j++;
	while (s[i] != '\0')
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			j++;
		i++;
	}
	return (j);
}

static char	**ft_print(char **fr, char const *s, char c, int j)
{
	int i;
	int k;
	int v;

	i = 0;
	k = 0;
	v = 0;
	while (k < j)
	{
		while (s[v] && s[v] == c)
			v++;
		while (s[v] && s[v] != c)
			fr[k][i++] = s[v++];
		fr[k][i] = '\0';
		i = 0;
		k++;
	}
	fr[k] = 0;
	return (fr);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**fr;
	int		i;
	int		j;
	int		d;

	if (!s || !c)
		return (NULL);
	d = ft_strlen(s);
	if (d == 0)
		j = 0;
	else
		j = ft_compte(s, c);
	if (!(fr = (char **)malloc(sizeof(char *) * (j + 1))))
		return (NULL);
	i = 0;
	while (i < j)
	{
		if (!(fr[i] = (char *)malloc(sizeof(char) * (d + 1))))
			return (NULL);
		i++;
	}
	fr = ft_print(fr, s, c, j);
	return (fr);
}
