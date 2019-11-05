/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_func_h_strr2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 03:42:48 by onouaman          #+#    #+#             */
/*   Updated: 2019/05/03 06:32:16 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stdio.h>


char		**alloc_chain(char **env, int nbr)
{
	char	**new_env;
	int		i;

	i = 0;
	if (*env == NULL || *env == NULL)
		return (NULL);
	new_env = (char **)malloc(sizeof(*new_env) * (ft_strrlen(env) + nbr + 1));
	while (env[i] && env[i] != NULL)
	{
		new_env[i] = ft_strnew(ft_strlen(env[i]));
		new_env[i] = ft_strcpy(new_env[i], env[i]);
		i++;
	}
	while (nbr > 0)
	{
		new_env[i] = NULL;
		nbr--;
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
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

char		*ft_strfreejoin(char *s1, char *s2)
{
	char			*result;
	unsigned int	len;
	unsigned int	i;
	unsigned int	j;

	j = 0;
	i = 0;
	if (!s1 && !s2)
		return (NULL);
	else if (!s1)
		return (ft_strdup(s2));
	else if (!s2)
		return (ft_strdup(s1));
	len = ft_strlen(s1);
	if ((result = malloc(len + ft_strlen(s2) + 1)))
	{
		ft_strcpy(result, s1);
		ft_strcpy(result + len, s2);
	}
	free(s1);
	free(s2);
	return (result);
}

char		*ft_str_trim(char *str)
{
	int	i;
	int	len_spc;

	i = 0;
	len_spc = 0;
	if (!str)
		return (NULL);
	if (!ft_isspace(str[0]) && !ft_isspace(str[ft_strlen(str) - 1]))
		return (str);
	while (ft_isspace(str[i++]))
		len_spc++;
	if (len_spc != 0)
		str = ft_strcpy(str, &str[len_spc]);
	len_spc = 0;
	if ((i = ft_strlen(str) - 1) > 0)
	{
		while (i >= 0 && ft_isspace(str[i]))
			str[i--] = 0;
	}
	return (str);
}
void		ft_strr_trim(char **args)
{
	if (!args)
		return ;
	while (*args)
	{
		*args = ft_str_trim(*args);
		args++;
	}
}