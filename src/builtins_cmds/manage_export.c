/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhri <aboukhri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 20:58:00 by aboukhri          #+#    #+#             */
/*   Updated: 2019/12/02 00:04:19 by aboukhri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static	int		export_flags_return(t_tokens **st_tokens, int index, int *n)
{
	int	j;
	int	c;

	j = 0;
	while ((*st_tokens) && (*st_tokens)->value[++j])
	{
		c = (*st_tokens)->value[j];
		if (c != 'n' && c != 'p')
			return (c);
		(c == 'n') && (*n = 1);
		if (!(*st_tokens)->value[j + 1] && (*st_tokens)->next
				&& (*st_tokens)->next->indx == index)
		{
			*st_tokens = (*st_tokens)->next;
			j = -1;
		}
	}
	return (0);
}

int				export_flags(t_tokens **st_tokens, int *n)
{
	int		i;
	int		c;

	*n = 0;
	if (!*st_tokens)
		return (0);
	i = (*st_tokens)->indx;
	while (*st_tokens)
	{
		if ((*st_tokens)->indx == i)
		{
			if ((*st_tokens)->value[0] != '-')
				return (0);
			if ((c = export_flags_return(st_tokens, i, n)))
				return (c);
			i++;
		}
		*st_tokens = (*st_tokens)->next;
	}
	return (0);
}

/*
**	display list of exports if no args given or if -p flag is present
*/

static	void	display_export(t_intern *export)
{
	t_intern	*lst;

	lst = export;
	while (lst)
	{
		ft_putstr("export ");
		ft_putstr(lst->key);
		if (lst->value)
		{
			ft_putchar('=');
			ft_putchar('"');
			ft_putstr(lst->value);
			ft_putchar('"');
		}
		ft_putchar('\n');
		lst = lst->next;
	}
}

/*
**	remove, edit, add, display export variables
*/

void			exported_vars(t_intern vrb, int rest, int edit)
{
	static	t_intern	*export;
	char				*line;

	if (rest == STDIN_FILENO)
	{
		if (add_intern_var(&export, vrb.key, vrb.value, edit))
		{
			line = ft_strjoir(ft_strjoin(vrb.key, "="), vrb.value, 1);
			ft_set_vrb(line, &g_environ, 1);
		}
	}
	else if (rest == STDOUT_FILENO)
		display_export(export);
	else if (rest == STDERR_FILENO)
		delete_intern_var(vrb.key, &export);
}
