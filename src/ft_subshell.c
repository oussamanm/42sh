/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_subshell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 23:42:21 by onouaman          #+#    #+#             */
/*   Updated: 2019/10/02 23:42:22 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "read_line.h"

/*
**	Function read for sub_shell incomplet cyntax 
*/

static void     ft_read_subsh(char **line, t_select *select, t_history *his)
{
	char	*temp;

	temp = NULL;
	*line = ft_strjoir(*line, "\n", 1);
	ft_putstr("sub> ");
	ft_read_line(his, select, 5);
	temp = ft_strdup(g_pos.cmd);
	ft_quotes(&temp, select, his);
	*line = ft_strjoir(*line, temp, 3);
}

/*
**	Check incomplet syntax of sub_shell and correct it 
*/

int				ft_check_subsh(int i, char **line, t_select *select, t_history *his)
{
	int			rtn;
	static int	s_count;

	rtn = 0;
	s_count = (!i) ? 0 : s_count;
	if (i >= (int)ft_strlen(*line) && s_count && !(*line)[i])
		ft_read_subsh(line, select, his);
	while ((*line)[i])
	{
		if ((*line)[i] == '(')
		{
			s_count++;
			rtn = ft_check_subsh(i + 1, line, select, his);
			i = rtn;
		}
		else if ((*line)[i] == ')')
		{
			s_count--;
			return (i);
		}
		if (s_count && !(*line)[i + 1])
			ft_read_subsh(line, select, his);
		i++;
	}
	return (rtn);
}

/*
**	Apply sub_shell
*/

void			ft_apply_subsh(t_cmds *st_cmds)
{
    UNUSED(st_cmds);
    /*
    t_tokens	*st_tokens;
    pid_t		pid;
    int			fds[2];
    char		buff[10];
    char		*str_resu;

    if (!st_cmds)
        return ;
    if (!ft_check_token(st_cmds->st_tokens, T_SUBSHL))
        return ;
    ft_bzero(&fds, 2);
    ft_bzero(&buff, 10);
    st_tokens = st_cmds->st_tokens;
    while (st_tokens)
    {
        if (st_tokens->token == T_SUBSHL)
        {
            if (pipe(fds) == -1)
                ft_putstr_fd("Error in create pipe in sub_shell\n", 2);

            if ((pid = fork()) == 0)
            {
                //if (dup2(fds[1], 1) == -1)
                //	ft_putstr_fd("Error in dup 1 of process\n", 2);
                sleep(5);
                ft_putstr_fd("world\n", fds[1]);
                close(fds[1]);
                //ft_cmds_setup(st_tokens->value);
                exit(0);
            }
            str_resu = ft_strnew(0);
            while (read(fds[0], buff, 10) > 0)
            {
                str_resu = ft_strjoir(str_resu, buff, 1);
                ft_bzero(&buff, 10);
                printf("buff = %s \n",buff);
            }
            printf("result = %s \n",str_resu);
            wait(NULL);
        }
        st_tokens = st_tokens->next;
    }
    */
}