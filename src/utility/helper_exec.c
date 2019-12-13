/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhri <aboukhri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 19:09:00 by onouaman          #+#    #+#             */
/*   Updated: 2019/12/08 23:05:48 by aboukhri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Get last tokens
*/

t_tokens	*get_last_token(t_tokens *st_tokens)
{
	if (!st_tokens)
		return (NULL);
	while (st_tokens && st_tokens->next)
		st_tokens = NEXT;
	return (st_tokens);
}

/*
** Correct token by remove all arg of T_EQUAL : variable = value
*/

void		correct_tokens(t_pipes *st_pipes)
{
	t_tokens	*st_tokens;
	t_tokens	*head;

	if (!st_pipes || !st_pipes->st_tokens)
		return ;
	st_tokens = st_pipes->st_tokens;
	head = st_tokens;
	while (st_tokens && (st_tokens->is_arg == T_EQUAL ||
		st_tokens->token == T_EQUAL))
	{
		st_tokens = NEXT;
		free(head);
		head = st_tokens;
	}
	st_pipes->st_tokens = head;
}

/*
** Remove escaped_character from cmd befor execution
*/

void		remove_backslashs(t_tokens *st_tokens)
{
	int		index;
	char	*arg;
	int		i;

	while (st_tokens)
	{
		if ((st_tokens->token == T_TXT || st_tokens->token == T_DQUO)
			&& (arg = st_tokens->value))
		{
			i = -1;
			while (arg[++i] && (index = ft_find_char(&arg[i], '\\')) != -1)
			{
				i += index;
				if (st_tokens->token == T_DQUO && M_SPEC_CHARC(arg[i + 1]))
					ft_strcpy(&arg[i], &arg[i + 1]);
				else if (st_tokens->token == T_TXT)
					ft_strcpy(&arg[i], &arg[i + 1]);
			}
		}
		st_tokens = NEXT;
	}
}

/*
**	Function set is_arg variable in list tokens : (is argument of T_EQUAL)
*/

void		set_isarg(t_pipes *st_pipes)
{
	t_tokens	*st_tokens;
	int			i;

	st_tokens = st_pipes->st_tokens;
	i = st_tokens->indx - 1;
	while (st_tokens)
	{
		if (st_tokens->indx == i)
			st_tokens = st_tokens->next;
		else
		{
			i++;
			if (!ft_is_equal(i, st_tokens))
				break ;
			if (!valid_identifier(st_tokens->value))
				return ;
			while (st_tokens && st_tokens->indx == i)
			{
				st_tokens->is_arg = T_EQUAL;
				st_tokens = st_tokens->next;
			}
		}
	}
}

/*
** Check if exist Cmd : check if Ok and permission
*/

int			ft_check_cmd(char *str_cmd, char **args)
{
	int			rtn;
	struct stat	st_stat;

	rtn = 0;
	if (str_cmd && str_cmd == args[0])
	{
		if (access(str_cmd, F_OK) != 0 && ++rtn)
			print_error(FIL_NS, NULL, str_cmd, 0);
		else if (!lstat(str_cmd, &st_stat) && S_ISDIR(st_stat.st_mode) && ++rtn)
			print_error(IS_DIR, NULL, str_cmd, 0);
	}
	if (!rtn && str_cmd && (access(str_cmd, X_OK) || access(str_cmd, R_OK)))
	{
		print_error(FIL_PD, NULL, args[0], 0);
		rtn = EXIT_FAILURE;
	}
	else if (!str_cmd || !ft_strlen(str_cmd))
	{
		print_error(CMD_NF, NULL, args[0], 0);
		rtn = EXIT_CMD_NF;
	}
	return (rtn);
}
