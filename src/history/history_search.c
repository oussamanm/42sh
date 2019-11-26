/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_search.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhri <aboukhri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 12:19:07 by aboukhri          #+#    #+#             */
/*   Updated: 2019/11/24 19:02:38 by aboukhri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/read_line.h"

t_info *history_strstr(t_info *last, char *search)
{
    while (last)
    {
        if (ft_strstr(last->cmd, search))
            return (last);
        last = last->prev;
    }
    return (NULL);
}

static void his_edit_line(char *search, char *res, char **cmd)
{
    if (res)
        his_new_line(res, cmd, &g_pos);
    ft_putstr_term(g_pos.num_col, *cmd + g_pos.index, &g_pos);

    tputs(tgetstr("do", NULL), 0, my_outc);
    tputs(tgoto(tgetstr("ch", NULL), 0, 0), 0, my_outc);
    tputs(tgetstr("cd", NULL), 0, my_outc);
    if (!res)
        ft_putstr("failing ");
    ft_putstr("bck-i-search: ");
    ft_putstr(search);
    
    //move cursor to the first chachter in search
}//ft_set_last_position(*pos, pos->num_lines); must be in the end of line  ft_get_end_of_line_pos(pos, s, pos->num_col);

void    history_search(t_history his, char **s)//??
{
    //char buff[6];
    //char *search;
    //char *res;

    his.len = 0;
    his_edit_line(NULL, NULL, s);
    /*ft_bzero(buff, 6);
    while (read(0, buff, 6))
    {
        if (DEL == CAST(buff))
            search = ft_delcolomn(search, &g_pos);//delete charachter from search
        else if (ft_isallprint(buff))
            search = ft_strjoir(search, buff, 1);
        else
            break ;
        his_edit_line()
        ft_bzero(buff, 6);
    }*/
}