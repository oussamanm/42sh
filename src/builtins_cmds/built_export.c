/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhri <aboukhri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 07:28:51 by aboukhri          #+#    #+#             */
/*   Updated: 2019/12/01 22:05:12 by aboukhri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**	display export usage
*/

static	void	export_usage(char c)
{
	ft_putstr_fd("42sh: export: -", 2);
	ft_putchar_fd(c, 2);
	ft_putendl_fd(": invalid option", 2);
	ft_putendl_fd("export: usage: export [-n] "\
			"[name[=value] ...] or export -p", 2);
}

static	void	setup_vrb(t_tokens *st_tokens, t_intern vrb, int index, int n)
{
	char	*temp;

	if (n)
	{
		exported_vars(vrb, STDERR_FILENO, -1);
		ft_unset_vrb(vrb.key, &g_environ);
	}
	else if (NEXT && NEXT->token == T_EQUAL && NEXT->indx == index)
	{
		temp = ft_strjoin(st_tokens->value, "=");
		if (NEXT->next && NEXT->next->indx == index &&
			T_IS_TXT(NEXT->next->token))
			temp = ft_strjoir(temp, NEXT->next->value, 0);
		ft_set_vrb(temp, &g_environ, 1);
		add_intern_var(&g_intern, vrb.key, vrb.value, 1);
		exported_vars(vrb, STDIN_FILENO, 0);
	}
	else
		move_to_env(vrb.key);
}

static	int		setup_export(t_tokens *st_tokens, int n)
{
	t_intern	vrb;
	int			i;

	i = st_tokens->indx;
	while (st_tokens)
	{
		if (st_tokens->indx != i)
		{
			st_tokens = NEXT;
			continue ;
		}
		if (!valid_identifier(st_tokens->value))
		{
			puterr_identifier(st_tokens->value, "export");
			return (0);
		}
		vrb = get_key_value(st_tokens);
		setup_vrb(st_tokens, vrb, i, n);
		i++;
	}
	return (1);
}

int				built_export(t_tokens *st_tokens)
{
	int	n;
	int	c;

	st_tokens = NEXT;
	if ((c = export_flags(&st_tokens, &n)))
	{
		export_usage(c);
		return (EXIT_FAILURE);
	}
	if (!st_tokens)
	{
		exported_vars((t_intern){NULL, NULL, NULL}, STDOUT_FILENO, -1);
		return (EXIT_SUCCESS);
	}
	if (!setup_export(st_tokens, n))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
