/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_func_help.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 23:29:51 by onouaman          #+#    #+#             */
/*   Updated: 2019/05/03 06:33:24 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void		ft_free_join(char **str1, char **str2, int rm)
{
	if (rm == 1 || rm == 3)
		ft_strrdel(str1);
	if (rm == 2 || rm == 3)
		ft_strrdel(str2);
}

void		ft_bchar(char *str, size_t n, char c)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		str[i] = c;
		i++;
	}
}

char		**ft_strr_new(int len)
{
	char	**args;
	int		i;

	i = 0;
	if ((args = (char **)malloc(sizeof(char *) * (len + 1))) == NULL)
	{
		ft_putendl_fd("Error in allocation\n", 2);
		return (NULL);
	}
	while (i < len)
	{
		args[i++] = NULL;
	}
	args[i] = NULL;
	return (args);
}
