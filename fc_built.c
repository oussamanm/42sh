/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_built.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhri <aboukhri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 15:45:42 by aboukhri          #+#    #+#             */
/*   Updated: 2019/11/15 22:54:52 by aboukhri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/read_line.h"
#include "includes/shell.h"

//read fc flags from fc builtin
t_history *history_between(t_history *his, char *src, char *dest)
{
    t_history *cont;
    t_info *ptr;
    int     index;

    if (ft_isdigit(src[0]))
    {
        index = ft_atoi(src);
        ptr = (his->len - index < index) ? his->tail : his->head;
        if ((cont->head = history_index(ptr, index, his->len)))
            return (NULL);
    }
    else if (!(cont->tail = history_keyword(his->tail, dest, 0)))
            return (NULL);
    if (ft_isdigit(dest))
    {
        index = ft_atoi(dest);
        ptr = (his->len - index < index) ? his->tail : his->head;
        if ((cont->tail = history_index(ptr, index, his->len)))
            return (NULL);
    }
    else
    {
        if (!(cont->tail = history_keyword(his->tail, dest, 0)))
            return (NULL);
    }
    return (cont);
}

char    *history_content(t_history his)
{
    t_info *head;
    char *content;

    if (!his.head || !his.tail)
        return (NULL);
    content = NULL;
    head = his.head;
    while (head)
    {
        content = (!content) ? ft_strdup(head->cmd) : ft_strjoir(content, head->cmd, 1);
        if (his.tail && his.tail->index == head->index)
            break ;
        head = (head->index < his.tail->index) ? head->next : head->prev;
    }
    return (content);
}


void    fc_edit(char **args, t_history history)
{
    char *content;
    int len;
    t_history value;

    len = ft_strrlen(args);
    content = NULL;
    if (!len && history.tail)
        content = ft_strdup(history.tail);
    else if (len == 1 && (value.head = history_keyword(history.tail, args[0], 0)))
        content = ft_strdup(value.head->cmd);
    else if (len > 1)
    {
        value.head = history_value(history, args[0]);
        value.tail = history_value(history, args[1]);
        content = history_content(value);
    }
    if (!content)
    {
        ft_putendl_fd("42sh: fc: history specification out of range", 2);
        return ;
    }
    write_fc(content);
    free(content);
    exec_fc();
}

/*
*  execute command from history after edited using text editor set in envirement using fc builtin
*/
void    exec_fc()
{
    pid_t child;
    char *line;
    char *cmd;
    char *args[3];

    cmd = ft_get_vrb("FCEDIT", g_environ);
    args[0] = (!cmd) ? "vi" : cmd;
    args[1] = "42sh-fc";
    args[2] = NULL;
    child = fork();
    if (child == 0)
        ft_cmd_exec(args, g_environ);
    else if (child > 0)
    {
        wait(NULL);
        if (line = read_fc())
            ft_multi_cmd(line);
    }
    if (cmd)
        free(cmd);
}



int    read_fc_flags(char **args, char **fl)
{
    int i;
    int j;
    char c;

    i = -1;
    *fl = NULL;
    while (args[++i] && args[i][0] == '-')
    {
        j = 0;
        while (args[i][++j])
        {
            c = args[i][j];
            if (c == 'l' || c == 'n' || c == 'r' || c == 'e')
                *fl = (!*fl) ? ft_strdup(&c) : ft_strjoir(*fl, &c, 1);
            else
            {
                free(*fl);
                return (c);
            }
        }
    }
    return (0);
}

void    rev_his_list(t_history *lst)
{
    t_info *tmp;

    tmp = lst->head;
    lst->head = lst->tail;
    lst->tail = tmp;
}

void    fc_built(char **args, t_history history)
{
    char *flags;
    char c;
    
    if ((c = read_fc_flags(args, &flags)))
    {
        ft_putstr_fd("42sh: fc: -", 2);
        ft_putchar_fd(c, 2);
        ft_putendl_fd(": invalid option\nfc: usage: fc [-e ename] [-nlr] [fisrt] [last]", 2);
        return ;
    }
    if (!flags)
        fc_edit(args, history);
    else
    {
        if (ft_strchr(flags, 's'))//reexecute the command take just first arg
            fc_s(history.tail, args[0]);
        else if (ft_strchr(flags, 'l'))//list of history
        {
            
            /*flags working with l:
                                    -n without indexes
                                    -r reverse list
                                    -e 
                                    */
        }
        else if (ft_strchr(flags, 'e')) //set editor text
        {
            
        }
    }
}

t_history fc_l_from_to(t_info *last, int len, int from, int to)
{
    t_history lst;
    

    init_history(&lst);
    if (!(lst.head = history_index(last, from, len)))
        return (lst);
    if (!(lst.tail = history_index(last, to, len)))
    {
        if (to > from)
            lst.tail = last;
        else
            return (lst);
    }
    lst.len = lst.tail->index - lst.head->index;
    return (lst);
}

void    fc_flag_l(t_history history, char *flags, char **args)
{
    t_history lst;

    lst = fc_l_list(history, args[0], args[1]);
    if (ft_strchr(flags, 'r'))
        rev_his_list(&lst);
    if (!t_strchr(flags, 'n'))
        unerdored_his_list(lst);
    else
        ordered_his_list(lst);
}

t_history    fc_l_list(t_history his, char *from, char *to)
{
    t_history lst;

    init_history(&lst);
    if (!from && !to)
        lst = fc_l_from_to(his.tail, his.len, his.len - 15, his.len);
    else if (!to && ft_str_alpha(from))
        lst = fc_l_from_to(his.tail, his.len, ft_atoi(from), his.len);
    else if (from && to && ft_str_alpha(from) && ft_str_alpha(to))
        lst = fc_l_from_to(his.tail, his.len, ft_atoi(from), ft_atoi(to));
    return (lst);

}

void    fc_s(t_info *tail, char *arg)
{
    char *cmd;

    if (!tail)
        return (NULL);
    if (!arg)
        cmd = tail->cmd;
    else
        cmd = history_keyword(tail, arg, 0);
    //execute command
    //insert in history
}





/** fc file management **/
char    *read_fc()
{
    int fd;
    char buff[1001];
    char *cmd;
    int rt;

    cmd = NULL;
    if ((fd = open("42sh-fc", O_RDONLY)))
    {
        while ((rt = read(fd, buff, 1000)) > 0)
        {
            cmd = (!cmd) ? ft_strdup(buff) : ft_strjoir(cmd, buff, 1);
            if (rt == 1000)
                ft_bzero(buff, 1000);
        }
        close(fd);
    }
    return (cmd);
}

void    write_fc(char *content)
{
    int fd;

    fd = open("42sh-fc", O_CREAT, O_TRUNC, O_WRONLY);
    ft_putstr_fd(content, fd);
    close(fd);
}