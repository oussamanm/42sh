/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_l.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhri <aboukhri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 00:09:35 by aboukhri          #+#    #+#             */
/*   Updated: 2019/11/22 01:59:42 by aboukhri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/read_line.h"
#include "../../includes/shell.h"

t_info       *fc_value(t_history his, char *keyword)
{
    int index;
    t_info *ptr;

    if (ft_isdigit(keyword[0]) || (keyword[0] == '-' && ft_isdigit(keyword[1])))
    {
        index = ft_atoi(keyword);
        if(index > his.len)
            index = his.len;
        if (index <= 0)
            index = his.len + index;
        ptr = (his.len - index < index) ? his.tail : his.head;
        return (history_index(ptr, index, his.len));
    }
    return (history_keyword(his.tail, keyword, 0));
}

static t_history    fc_l_list(t_history his, char *from, char *to)
{
    t_history lst;
    int jk;

    init_history(&lst);
    if (!his.head || !his.tail)
        return (lst);
    if (from)
        lst.head = fc_value(his, from);
    else
    {
        jk = (his.len > 15) ? his.len - 15 : his.head->index;
        lst.head = history_index(his.tail, jk, his.len);
    }
    if (to)
       lst.tail = fc_value(his, to);
    else
        lst.tail = his.tail;
    return (lst);
}

/*
**   show list from index depends on the the arguments given
*/

void    fc_flag_l(t_history history, char *flags, char **args)
{
    t_history lst;

    lst = fc_l_list(history, args[0], args[1]);
    if (!lst.head || !lst.tail)
    {
        ft_putendl_fd("42sh: fc: history specification out of range", 2);
        return ;
    }
    if (ft_strchr(flags, 'r'))
        rev_his_list(&lst);
    if (ft_strchr(flags, 'n'))
        display_his_list(lst, 0);
    else
        display_his_list(lst, 1);
}