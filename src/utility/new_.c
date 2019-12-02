/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 04:16:28 by onouaman          #+#    #+#             */
/*   Updated: 2019/12/02 04:16:30 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_redir		*ft_new_redir(void)
{
	t_redir	*st_redir;

	if ((st_redir = (t_redir *)malloc(sizeof(t_redir))) == NULL)
		return (NULL);
	st_redir->next = NULL;
	return (st_redir);
}

t_intern	*new_intern(char *key, char *value)
{
	t_intern *new;

	if (!(new = (t_intern*)malloc(sizeof(t_intern))))
		return (NULL);
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->next = NULL;
	return (new);
}
