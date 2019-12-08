/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_flags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhri <aboukhri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 11:05:50 by aboukhri          #+#    #+#             */
/*   Updated: 2019/12/07 19:55:50 by aboukhri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/read_line.h"

/*
**	read fc flags and save them in string and return the position
**	of args after flags or return -1 in case flag not exist
*/

int		read_fc_flags(char **args, char **fl, char *err)
{
	int		i;
	int		j;
	char	c;

	i = -1;
	*fl = NULL;
	while (args && args[++i] && args[i][0] == '-' && !ft_isdigit(args[i][1]))
	{
		j = 0;
		while (args[i][++j])
		{
			c = args[i][j];
			if (c == 'l' || c == 'n' || c == 'r' || c == 's' || c == 'e')
				*fl = (!*fl) ? ft_strdup(&c) : ft_strjoir(*fl, &c, 1);
			else
			{
				ft_strdel(fl);
				(err) && (*err = c);
				return (-1);
			}
		}
	}
	return (i);
}

/*
**	in case of error display usage message
*/

void	fc_usage(char c, char *msg)
{
	ft_putstr_fd("42sh: fc: -", 2);
	ft_putchar_fd(c, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(msg, 2);
	ft_putendl_fd("fc: usage: fc [-e ename]"\
			"[-nlr] [fisrt] [last]", 2);
}

int		fc_flag_e(t_history his, char **args)
{
	if (!args[0])
	{
		fc_usage('e', "option requires an argument");
		return (EXIT_FAILURE);
	}
	else
	{
		if (fc_edit(his, args[0], NULL, args + 1))
			return (EXIT_FAILURE);
		exec_fc();
		if (access(".42sh-fc", F_OK) == 0)
		{
			ft_putendl("llllllllll");
			ft_multi_cmd("rm .42sh-fc", 0);
		}
	}
	return (EXIT_SUCCESS);
}

int		fc_flag_s(t_history *his, char *arg)
{
	char	*cmd;
	t_info	*val;

	cmd = NULL;
	if (!arg)
		cmd = ft_strdup(his->tail->cmd);
	else if ((val = fc_value(*his, arg)))
		cmd = ft_strdup(val->cmd);
	if (cmd)
	{
		ft_putendl(cmd);
		insert_history(his, cmd);
		history_readline(his, 0, NULL);
		ft_multi_cmd(cmd, 0);
		ft_strdel(&cmd);
	}
	else
	{
		ft_putendl_fd("42sh: fc: no command found", 2);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
