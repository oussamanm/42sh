/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhri <aboukhri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 15:11:40 by aboukhri          #+#    #+#             */
/*   Updated: 2019/11/22 01:58:55 by aboukhri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/read_line.h"

/* initialize pointers to NULL  */
void init_history(t_history *history)
{
    history->head = NULL;
    history->tail = NULL;
    history->len = 0;
    history->bg = 0;
}
/* set new env var if not exist
    EDIT TEXT of fc commad is vim by default*/
void init_fc_built()
{
    ft_set_vrb("FCEDIT=vi", &g_environ, 0);
}

/* restore history in the begining of program */
void    restore_history(t_history *history)
{
    char *line;
    int fd;

    init_history(history);
    fd = open(".42sh_history", O_RDONLY);
    line = NULL;
    while (get_next_line(fd, &line) > 0)
    {
        insert_history(history, line);
        ft_strdel(&line);
    }
    history->bg = history->len + 1;
    //printf("%d  |  %d\n", history->bg, history->len);
    close(fd);
}

/* save the inserted commands in the current session bfore */
void    save_history(t_history *history)
{
    t_info *lst;
    int fd;

    //printf("%d  |  %d\n", history->bg, history->len);
    lst = (history->len - history->bg < history->bg - 1) ? history->tail : history->head;
    if (!(lst = history_index(lst, history->bg, history->len)))
        return ;
    //ft_putendl("create");
    fd = open(".42sh_history", O_WRONLY | O_APPEND | O_CREAT, 00600);
    while (lst)
    {
        write(fd, lst->cmd, ft_strlen(lst->cmd));
        write(fd, "\n", 1);
        lst = lst->next;
    }
    close(fd);
}

