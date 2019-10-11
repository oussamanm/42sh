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
** find file in PATH :
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
		{
			ft_strrdel(str_paths);
			return (temp);
		}
		ft_strdel(&temp);
	}
	ft_strrdel(str_paths);
	return (NULL);
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
			st_pipes = ft_new_pipe();
			head = st_pipes;
		}
		st_pipes->cmd = *args_pipe;
		st_pipes->fds[0] = 0;
		st_pipes->fds[1] = 1;
		args_pipe++;
		if (*args_pipe != NULL)
		{
			st_pipes->next = ft_new_pipe();
			st_pipes = st_pipes->next;
		}
	}
	return (head);
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
** Calculate sum of ASCI :
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
** Function remove quote from string
*/

char		*ft_rm_quot(char *str)
{
	char	*rtn;

	rtn = NULL;
	if (!str)
		return (NULL);
	rtn = ft_strdup(&str[1]);
	rtn[ft_strlen(rtn) - 1] = '\0';
	return (rtn);
}

int		find_char_escap(char *str, char c)
{
	int		i;

	i = 0;
	if (str == NULL)
		return (-1);
	while (str[i] != '\0')
	{
		if (str[i] == '\\')
		{
			i += (str[i + 1]) ? 2 : 1;
			continue ;
		}
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

