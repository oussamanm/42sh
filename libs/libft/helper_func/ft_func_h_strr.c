/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_func_h_strr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 03:37:32 by onouaman          #+#    #+#             */
/*   Updated: 2019/05/03 06:31:51 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char		**ft_strr_join(char **str1, char **str2)
{
	int		i;
	int		l1;
	int		l2;
	char	**new_chaine;

	i = -1;
	if (str1 == NULL || str2 == NULL)
		return (NULL);
	l1 = ft_strrlen(str1);
	l2 = ft_strrlen(str2);
	if ((new_chaine = (char **)malloc(sizeof(char **) * (l1 + l2 + 1))) == NULL)
		return (NULL);
	while (str1[++i] != NULL)
		new_chaine[i] = ft_strdup(str1[i]);
	l2 = 0;
	while (str2[l2] != NULL)
	{
		new_chaine[i++] = ft_strdup(str2[l2]);
		l2++;
	}
	new_chaine[i] = NULL;
	return (new_chaine);
}

int			ft_put_strr(char **str)
{
	int i;

	i = 0;
	if (str == NULL)
		return (-1);
	while (str[i] != NULL)
	{
		ft_putstr("---\n");
		ft_putendl(str[i]);
		ft_putstr("---\n");
		i++;
	}
	return (i);
}

char		**ft_strr_dup(char **chaine, int len)
{
	char	**new_chaine;
	int		i;

	if (!chaine || *chaine == NULL || len == 0)
		return (NULL);
	i = 0;
	if ((new_chaine = (char **)malloc(sizeof(char *) * (len + 1))) == NULL)
		return (NULL);
	while (chaine[i] && chaine[i] != NULL)
	{
		new_chaine[i] = ft_strdup(chaine[i]);
		i++;
	}
	while (i < (len + 1))
	{
		new_chaine[i] = NULL;
		i++;
	}
	return (new_chaine);
}

int			ft_strrlen(char **argv)
{
	int		i;

	i = 0;
	if (argv == NULL)
		return (-1);
	while (*argv && *argv != NULL)
	{
		i++;
		argv++;
	}
	return (i);
}

void		ft_strrdel(char **str)
{
	int		i;

	i = 0;
	if (str == NULL)
		return ;
	while (str[i])
	{
		ft_strdel(&str[i]);
		i++;
	}
	free(str);
	str = NULL;
}
