/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_other.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhri <aboukhri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 06:21:47 by aboukhri          #+#    #+#             */
/*   Updated: 2019/11/22 14:46:44 by aboukhri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/read_line.h"

char    is_shell_delimiter(char c)
{
    if (c == '|' || c == ';' || c == '>' || c == '<' || c == '&')
        return (c);
    return (0);
}

char *get_delimiter(char *keyword)
{
    int bg;
    int len;
    int i;

    bg = -1;
    len = 0;
    i = -1;
    while (keyword[++i])
    {
        if (is_shell_delimiter(keyword[i]) && bg == -1)
            bg = i;
        else if (keyword[i] == '!')
            break ;
        (bg >= 0) && (len++);
    }
    if (len == 0)
        return (NULL);
    return (ft_strsub(keyword, bg, len));
}

char    *str_notnumber(char *keyword)
{
    int i;

    i = -1;
    while (keyword[++i])
    {
        if (!ft_isdigit(keyword[i]))
            return (keyword + i);
    }
    return (NULL);
}

void    rev_his_list(t_history *lst)
{
    t_info *tmp;

    tmp = lst->head;
    lst->head = lst->tail;
    lst->tail = tmp;
}