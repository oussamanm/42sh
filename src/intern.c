/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intern.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 21:41:01 by onouaman          #+#    #+#             */
/*   Updated: 2019/09/24 21:41:04 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/****** intern variable management ***** */


void		add_intern_var(char *key, char *value)
{
    char *line;
    t_intern *lst;

    line = ft_strjoir(ft_strjoin(key, "="), value, 1);
    if (ft_edit_vrb(line, &g_environ))
        return ;
    if (!(g_intern))
        g_intern = new_intern(key, value);
    else
    {
        lst = g_intern;
        while (lst)
        {
            if (ft_strcmp(lst->key, key) == 0)
            {
                free(lst->value);
                lst->value = ft_strdup(value);
                return ;
            }
            if (!lst->next)
                break;
            lst = lst->next;
        }
        lst->next = new_intern(key, value);
    }
}

void		delete_intern_var(char *key, t_intern **head)
{
    t_intern *lst;
    t_intern *next;

    lst = *head;
    while (lst)
    {
        if (ft_strcmp(lst->value, key) == 0)
        {
            next = lst->next;
            free(lst->key);
            free(lst->value);
            free(lst);
            lst = next;
            break;
        }
        lst = lst->next;
    }
}

t_intern	get_key_value(t_tokens *st_tokens)
{
	t_intern	var;

	var.key = st_tokens->value;
	st_tokens->is_arg = T_EQUAL;
	if (NEXT && NEXT->next && NEXT->next->indx == st_tokens->indx)
	{
		NEXT->next->is_arg = T_EQUAL;
		var.value = NEXT->next->value;
	}
	else
		var.value = "";
	NEXT->is_arg = T_EQUAL;
	return (var);
}

char        **parse_var(char *line)
{
    char **vars;
	int		i;

    if (!(vars = (char**)ft_memalloc(sizeof(char*) * 3)))
        return (NULL);
	i = ft_find_char(line, '=');
	vars[0] = ft_strsub(line, 0, i);
	vars[1] = ft_strsub(line, i, ft_strlen(line));
    return (vars);
}

char		*get_intern_value(char *key)
{
    t_intern *lst;

    lst = g_intern;
    while (lst)
    {
        if (ft_strcmp(key, lst->key) == 0)
            return (lst->value);
        lst = lst->next;
    }
    return (NULL);
}