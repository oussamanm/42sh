/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_variab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 12:01:46 by onouaman          #+#    #+#             */
/*   Updated: 2019/12/02 12:01:48 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**	ft_get_vrb : return variable (allocated) || NULL :
*/

char		*ft_get_vrb(char *vrb, char **env)
{
	int		len;
	char	*value;

	if (vrb == NULL || env == NULL)
		return (NULL);
	if ((len = ft_strlen(vrb)) == 0)
		return (NULL);
	while (*env != NULL)
	{
		if (ft_strnequ(*env, vrb, len) && (*env)[len] == '=')
		{
			value = ft_strsub(*env, len + 1, ft_strlen(*env) - len - 1);
			return (value);
		}
		env++;
	}
	return (NULL);
}
