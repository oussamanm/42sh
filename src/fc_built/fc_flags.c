/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_flags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhri <aboukhri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 11:05:50 by aboukhri          #+#    #+#             */
/*   Updated: 2019/11/22 14:54:04 by aboukhri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/read_line.h"

/*  read fc flags and save them in string and return the position of args after flags or return -1 in case flag not exist */
int    read_fc_flags(char **args, char **fl, char *err)
{
    int i;
    int j;
    char c;

    i = -1;
    *fl = NULL;
    while (args[++i] && args[i][0] == '-' && !ft_isdigit(args[i][1]))
    {
        j = 0;
        while (args[i][++j])
        {
            c = args[i][j];
            if (c == 'l' || c == 'n' || c == 'r' || c == 's' || c == 'e')
                *fl = (!*fl) ? ft_strdup(&c) : ft_strjoir(*fl, &c, 1);
            else
            {
                if (*fl)
                    free(*fl);
                (err) && (*err = c);
                return (-1);
            }
        }
    }
    return (i);
}

/* check if fc builtin exists and in in cmd and has exec flags(e, s)*/
int		fc_exec_flag(char *str_cmds)
{
	char **pv_args;
	char **sp_args;
	int i;
	char *fl;

	if (!str_cmds)
		return (0);
	pv_args = ft_str_split_q(str_cmds, ";");
	sp_args = NULL;
	i = -1;
	while (pv_args && pv_args[++i])
	{
		sp_args = ft_str_split_q(pv_args[i], "\n \t");
		if (sp_args && ft_strcmp(sp_args[0], "fc") == 0)
		{
			if (read_fc_flags(sp_args + 1, &fl, NULL) &&
			(ft_strchr(fl, 'e') || ft_strchr(fl, 's')))
				return (1);
		}
        ft_strrdel(sp_args);
	}
	ft_strrdel(pv_args);
	return (0);
}

/*  in case of error display usage message */ 
void    fc_usage(char c)
{
    ft_putstr_fd("42sh: fc: -", 2);
    ft_putchar_fd(c, 2);
    ft_putendl_fd(": invalid option\nfc: usage: fc [-e ename] [-nlr] [fisrt] [last]", 2);
}

void    fc_flag_e(t_history his, char **args)
{
    if (!args[0])
    {
        fc_usage('e');
        return ;
    }
    else if (fc_edit(his, args[0], args + 1))
        exec_fc();
}

void    fc_flag_s(t_history his, char *arg)
{
    char *cmd;
    t_info *val;

    cmd = NULL;
    if (!arg)
        cmd = his.tail->cmd;
    else if ((val = fc_value(his, arg)))
        cmd = ft_strdup(val->cmd);
    if (cmd)
    {
        ft_putendl(cmd);
        insert_history(&g_history, cmd);
        ft_multi_cmd(cmd, 0);
        //exit??
    }
    else
        ft_putendl_fd("42sh: fc: no command found", 2);
}