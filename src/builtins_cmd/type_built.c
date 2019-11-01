/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_built.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 12:18:03 by mfilahi           #+#    #+#             */
/*   Updated: 2019/09/25 12:18:05 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int     is_builtin(char *arg)
{
    if (ft_strcmp(arg, "echo") == 0)
        return (1);
    else if (ft_strcmp(arg, "cd") == 0)
        return (1);
    else if (ft_strcmp(arg, "env") == 0)
        return (1);
    else if (ft_strcmp(arg, "setenv") == 0)
        return (1);
    else if (ft_strcmp(arg, "unsetenv") == 0)
        return (1);
    else if (ft_strcmp(arg, "type") == 0)
        return (1);
    return (0);
}

void    buil_putstr(char *arg, char *s1, char *s2, int fd)
{
    if (!s1 && !s2)
        ft_putendl_fd(arg, fd);
    else if (!s2)
    {
        ft_putstr_fd(arg, fd);
        ft_putendl_fd(s1, fd);
    }
    else
    {
        ft_putstr_fd(arg, fd);
        ft_putstr_fd(s1, fd);
        ft_putendl_fd(s2, fd);
    }
}

int     type_options_(char *arg, int *flag)
{
    while (*arg)
    {
        if (*arg == 'a')
			*flag = a_op(*arg, *flag);
		else if (*arg == 'p')
			*flag = p_op(*arg, *flag);
		else if (*arg == 'P')
			*flag = maj_p_op(*arg, *flag);
		else if (*arg == 't')
			*flag = t_op(*arg, *flag);
		else if (*arg == 'f' && !*(arg + 1))
			break ;
        arg++;
    }
    return (1);
}

int type_options(char **arg, int *flag)
{
    int i;
	int j;

    i = 0;
	while (arg[i])
	{
        if (arg[i][0] == '-')
        {
           if (t_fake_option(arg[i], &j))
           {
               print_error(TYPE_OEMSG, "42sh: type: -", &arg[i][j], 0);
               return (-1);
           }
           else if (type_options_(&arg[i][1], flag) == -1)
                return (i);
        }
        else
            return (i);
		i++;
	}
	return (i);
}

void   ft_buil_type_(char *args, int flag)
{
    if (flag == a_flg)
        a_option(args);
    else if (flag == p_flg)
        p_option(args, 0);
    else if (flag == maj_p_flg)
        p_option(args, 1);
    else if (flag == t_flg)
        t_option(args, 1);
    else if (flag == (a_flg | p_flg))
        p_option(args, 1);
    else if (flag == (a_flg | t_flg))
        at_option(args);
    else if (flag == (maj_p_flg | t_flg))
        t_option(args, 0);
}

int    built_type(char **args, char **tmpenv)
{
    int     flag;
    int     i;
    int     var;

    (void)tmpenv;
    flag = 0;
    if (!((i = type_options(args, &flag)) == -1))
        args += i;
    else 
        return (0);
    var = 0;
    while (*args)
    {
        if (!flag || flag == f_flg)
            no_options(*args, &var);
        else
            ft_buil_type_(*args, flag);
        args++;
    }
    return ((var) ? 1 : 0);
}