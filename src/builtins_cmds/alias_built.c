/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_built.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 14:45:31 by mfilahi           #+#    #+#             */
/*   Updated: 2019/11/15 18:10:31 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** look if arg has an alias and return him;
*/

char	**aliasmatched(char **args)
{
	t_aliaspkg	*data;
	t_alias		*curr;
	char		*temp;
	char		**rtn;

	data = storeaddrstruct(NULL);
	temp = ft_strjoin(args[0], "=");
	curr = data->head_ref;
	rtn = NULL;
	while (curr)
	{
		if (ft_strcmp(curr->shortcut, temp) == 0)
		{
			ft_strdel(&temp);
			temp = handleqoutes(ft_strdup(curr->cmd));
			rtn = ft_str_split_q(temp, " \t\n");
			rtn = ft_strr_join(rtn, &args[1], 1);
			ft_strrdel(args);
		}
		curr = curr->next;
	}
	ft_strdel(&temp);
	if (rtn)
		return (rtn);
	return (args);
}

/*
** Print a specific aliase for ex:cmd alias "x";
*/

void	printelement(char *shortcut)
{
	t_aliaspkg	*data;
	t_alias		*curr;
	char		*tmp;

	data = storeaddrstruct(NULL);
	curr = data->head_ref;
	tmp = ft_strjoin(shortcut, "=");
	while (curr)
	{
		if (ft_strcmp(curr->shortcut, tmp) == 0)
		{
			ft_putstr_fd("alias ", 1);
			ft_putstr_fd(curr->shortcut, 1);
			(curr->cmd[0] != '\'') ? ft_putchar_fd('\'', 1) : 0;
			ft_putstr_fd(curr->cmd, 1);
			(curr->cmd[ft_strlen(curr->cmd) - 1] != '\'') ?\
			ft_putendl_fd("\'", 1) : ft_putchar_fd('\n', 1);
			ft_strdel(&tmp);
			return ;
		}
		curr = curr->next;
	}
	print_error("not found", "alias: ", shortcut, 0);
}

/*
** push alias to list for example w="who";
*/

void	ft_built_alias_3(t_tokens *st_tokens, char *arg)
{
	char	*tmp;
	int		j;

	arg = ft_strjoir("", st_tokens->value, 0);
	arg = ft_strjoir(arg, NEXT->value, 1);
	if (NEXT && NEXT->next && NEXT->next->indx == st_tokens->indx)
		arg = ft_strjoir(arg, NEXT->next->value, 1);
	j = 0;
	while (arg[j] && arg[j] != '=')
		j++;
	tmp = ft_strsub(arg, 0, j);
	rm_alias_by_elem_flag(tmp, NULL, 0, 0);
	pushtolist(arg, 0);
	ft_strdel(&tmp);
	ft_strdel(&arg);
}

/*
** this func call to functions to push alias in list or to print all aliases;
*/

void	ft_buil_alias_2(t_tokens *st_tokens, char *arg)
{
	int i;

	i = 1;
	while (st_tokens)
	{
		if (st_tokens->indx == i)
		{
			if (NEXT && NEXT->token == T_EQUAL && NEXT->indx == st_tokens->indx)
				ft_built_alias_3(st_tokens, arg);
			else
				printelement(st_tokens->value);
			i++;
		}
		st_tokens = st_tokens->next;
	}
}

/*
** the main function of alias;
*/

void	ft_buil_alias(t_tokens *st_tokens)
{
	st_tokens = st_tokens->next;
	if (!st_tokens)
	{
		printlist();
		return ;
	}
	if (st_tokens->value[0] == '-')
	{
		print_error(" invalid option", "alias: ", st_tokens->value, 0);
		print_error("alias [name[=value] ... ]", NULL, "alias: usage: ", 0);
		return ;
	}
	ft_buil_alias_2(st_tokens, NULL);
}
