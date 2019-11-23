/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_built.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhri <aboukhri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 15:45:42 by aboukhri          #+#    #+#             */
/*   Updated: 2019/11/23 18:00:32 by aboukhri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/read_line.h"
#include "../../includes/shell.h"

static char *history_getcmds(t_history his, char **args, int r)
{
    int len;
    char *content;
    t_history value;

    len = ft_strrlen(args);
    content = NULL;
    if (!len && his.tail)
        content = ft_strdup(his.tail->cmd);
    else if (len == 1 && (value.head = fc_value(his, args[0])))
        content = ft_strdup(value.head->cmd);
    else if (len > 1)
    {
        value = (t_history){fc_value(his, args[0]), fc_value(his, args[1]), 0, 0};
        if (r)
            rev_his_list(&value);
        content = history_content(value);
    }
}

/*  edit commands given from arguments(index, string) by the editor given and re-execute them*/
int    fc_edit(t_history his, char *editor, char *flags, char **args)
{
    char *content;
    char *cmd;

    if (editor == NULL)
    {
        ft_putendl_fd("42sh: must specify editor in FCEDIT" , 2);
        return (0);
    }
    (flags) && (args++);
    if (!(content = history_getcmds(his, args, (ft_strchr(flags, 'r')))))
    {
        ft_putendl_fd("42sh: fc: history specification out of range", 2);
        return (0);
    }
    write_fc(content);
    free(content);
    cmd = ft_strjoin(editor, " .42sh-fc");
    ft_multi_cmd(cmd, 0);
    free(cmd);
    return (1);
}

/* execute commands edited from history */
void    exec_fc()
{
    char *content;
    char **cmds;
    int i;

    if (!(content = read_fc()))
        return ;
    cmds = ft_strsplit(content, '\n');
    i = -1;
    while (cmds && cmds[++i])
    {
        if (!history_handling(&cmds[i]))
            continue ;
        ft_putendl(cmds[i]);
        ft_multi_cmd(cmds[i], 0);
    }
    ft_strrdel(cmds);
}

void    fc_built(char **args, t_history *history)
{
    char *flags;
    char c;
    int pos;
    char *editor;

    if (!history->head || !history->tail)
        return ;
    if ((pos = read_fc_flags(args, &flags, &c)) == -1)
    {
        fc_usage(c);
        return ;
    }
    if (!flags || (!ft_strchr(flags, 's') && !ft_strchr(flags, 'e')))
        fc_edit(*history, ft_get_vrb("FCEDIT", g_environ), flags, args);
    else
    {
        if (ft_strchr(flags, 's'))//reexecute the command take just first arg
            fc_flag_s(history, *(args + pos));
        else if (ft_strchr(flags, 'e')) //set editor text
            fc_flag_e(*history, args + pos);
        else if (ft_strchr(flags, 'l'))//list of history
            fc_flag_l(*history, flags, args + pos);
    }
}