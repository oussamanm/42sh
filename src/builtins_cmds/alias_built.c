/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_built.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 14:45:31 by mfilahi           #+#    #+#             */
/*   Updated: 2019/11/26 18:31:47 by test             ###   ########.fr       */
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
	curr = data->head_ref;
	rtn = NULL;
	while (curr)
	{
		if (ft_strcmp(curr->shortcut, args[0]) == 0)
		{
			// temp = handleqoutes(ft_strdup(curr->cmd));
			temp = aliasfinder(curr, NULL, NULL);
			rtn = ft_str_split_q(temp, " \t\n");
			ft_strdel(&temp);
			rtn = ft_strr_join(rtn, &args[1], 1);
			break ;
		}
		curr = curr->next;
	}
	if (rtn)
		return (rtn);
	return (args);
}

/*
** Print a specific aliase for ex:cmd alias "x";
*/

void	printelement(char *shortcut, int *flag)
{
	t_aliaspkg	*data;
	t_alias		*curr;

	data = storeaddrstruct(NULL);
	curr = data->head_ref;
	while (curr)
	{
		if (ft_strcmp(curr->shortcut, shortcut) == 0)
		{
			ft_putstr_fd("alias ", 1);
			ft_putstr_fd(curr->shortcut, 1);
			ft_putstr_fd("=", 1);
			(curr->cmd[0] != '\'') ? ft_putchar_fd('\'', 1) : 0;
			ft_putstr_fd(curr->cmd, 1);
			(curr->cmd[ft_strlen(curr->cmd) - 1] != '\'') ?\
			ft_putendl_fd("\'", 1) : ft_putchar_fd('\n', 1);
			return ;
		}
		curr = curr->next;
	}
	print_error("not found", "alias: ", shortcut, 0);
	*flag = 1;
}

/*
** push alias to list for example w="who";
*/

void	ft_built_alias_3(t_tokens *st_tokens, char *arg)
{
	char	**arr;

	arg = ft_strjoir("", st_tokens->value, 0);
	arg = ft_strjoir(arg, NEXT->value, 1);
	if (NEXT && NEXT->next && NEXT->next->indx == st_tokens->indx)
		arg = ft_strjoir(arg, get_value_next(NEXT->next), 3);
	arr = ft_strsplit(arg, '=');
	rm_alias_by_elem_flag(arr[0]);
	if (!arr[1])
		arr[1] = ft_strdup("");
	pushtolist(arr[0], arr[1], 0);
	ft_strdel(arr);
	ft_strdel(&arg);
}

/*
** this func call to functions to push alias in list or to print all aliases;
*/

int		ft_buil_alias_2(t_tokens *st_tokens, char *arg)
{
	int i;
	int flag;

	i = 1;
	flag = 0;
	while (st_tokens)
	{
		if (st_tokens->indx == i)
		{
			if (NEXT && NEXT->token == T_EQUAL &&\
			NEXT->indx == st_tokens->indx &&\
			ft_strlen(st_tokens->value) > 0)
				ft_built_alias_3(st_tokens, arg);
			else
				printelement(st_tokens->value, &flag);
			i++;
		}
		st_tokens = st_tokens->next;
	}
	if (flag)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/*
** the main function of alias;
*/

int		ft_buil_alias(t_tokens *st_tokens)
{
	st_tokens = st_tokens->next;
	if (!st_tokens)
	{
		printlist();
		return (EXIT_SUCCESS);
	}
	if (st_tokens->value[0] == '-')
	{
		print_error("invalid option", "alias: ", st_tokens->value, 0);
		print_error("alias [name[=value] ... ]", NULL, "alias: usage: ", 0);
		return (EXIT_FAILURE);
	}
	if (ft_buil_alias_2(st_tokens, NULL) == 1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
