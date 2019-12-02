/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_helper_func.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 06:15:37 by onouaman          #+#    #+#             */
/*   Updated: 2019/05/03 06:21:40 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** find file in PATH
*/

char		*ft_find_path(char *arg, char **env)
{
	int		i;
	char	**str_paths;
	char	*temp;

	if (!arg || !ft_strlen(arg))
		return (NULL);
	i = -1;
	str_paths = NULL;
	if (env != NULL && *env != NULL && arg)
	{
		temp = ft_get_vrb("PATH", env);
		str_paths = (temp != NULL) ? ft_str_split(temp, ":") : NULL;
		ft_strdel(&temp);
	}
	while (str_paths != NULL && str_paths[++i] != NULL && arg)
	{
		str_paths[i] = ft_strjoir(str_paths[i], "/", 1);
		temp = ft_strjoir(str_paths[i], arg, 0);
		if (access(temp, F_OK) == 0)
			break ;
		ft_strdel(&temp);
	}
	ft_strrdel(str_paths);
	return (temp);
}

/*
** Print error and exit
*/

void		ft_err_exit(char *str)
{
	ft_putstr_fd(str, 2);
	exit(EXIT_FAILURE);
}

/*
** Check if exist redirection
*/

int			ft_check_redi(t_pipes *st_pipes)
{
	t_tokens	*st_temp;

	if (st_pipes == NULL || st_pipes->st_tokens == NULL)
		return (-1);
	st_temp = st_pipes->st_tokens;
	while (st_temp)
	{
		if (st_temp->token < 0)
			return (1);
		st_temp = st_temp->next;
	}
	return (0);
}

/*
** Calculate sum of ASCI
*/

int			ft_sum_asci(char str[])
{
	int	sum;

	if (str == NULL)
		return (0);
	sum = 0;
	while (*str != '\0')
	{
		sum += *str;
		str++;
	}
	return (sum);
}

/*
** Converte Result_cmd to tokens , work for sub_shell
*/

void		value_to_token(char *value, t_tokens **st_tokens)
{
	char		**args;
	int			index;
	int			i;
	t_tokens	*save_next;

	if (!st_tokens || !(*st_tokens))
		return ;
	i = 0;
	index = (*st_tokens)->indx;
	args = ft_str_split_q(value, " \n");
	save_next = (*st_tokens)->next;
	while (args[i])
	{
		ft_fill_token(st_tokens, T_TXT, args[i], index);
		index++;
		i++;
	}
	if (i != 0 && ((*st_tokens) = (*st_tokens)->prev))
	{
		free((*st_tokens)->next);
		(*st_tokens)->next = save_next;
		if (save_next)
			save_next->prev = (*st_tokens);
	}
	free(args);
}
