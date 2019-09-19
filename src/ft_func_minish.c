/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_func_minish.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 06:15:37 by onouaman          #+#    #+#             */
/*   Updated: 2019/05/03 06:21:40 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** find file in PATH :
*/

char		*ft_find_path(char *arg, char **env)
{
	int		i;
	char	**str_paths;
	char	*temp;

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
		{
			ft_strrdel(str_paths);
			return (temp);
		}
		ft_strdel(&temp);
	}
	ft_strrdel(str_paths);
	return (NULL);
}

t_pipes		*ft_new_stpipe(void)
{
	t_pipes *st_pipes;

	if ((st_pipes = (t_pipes *)malloc(sizeof(t_pipes))) == NULL)
		return (NULL);
	st_pipes->args = NULL;
	st_pipes->cmd = NULL;
	ft_bzero(st_pipes->fds, 2);
	st_pipes->st_redir = NULL;
	st_pipes->st_tokens = NULL;
	st_pipes->next = NULL;
	return (st_pipes);
}

/*
** Convert table of string to list : O
*/

t_pipes		*ft_strr_list(char **args_pipe)
{
	t_pipes *st_pipes;
	t_pipes *head;

	if (args_pipe == NULL)
		return (NULL);
	st_pipes = NULL;
	head = NULL;
	while (*args_pipe)
	{
		if (st_pipes == NULL)
		{
			st_pipes = ft_new_stpipe();
			head = st_pipes;
		}
		st_pipes->cmd = *args_pipe;
		st_pipes->fds[0] = 0;
		st_pipes->fds[1] = 1;
		args_pipe++;
		if (*args_pipe != NULL)
		{
			st_pipes->next = ft_new_stpipe();
			st_pipes = st_pipes->next;
		}
	}
	return (head);
}
