/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_search.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhri <aboukhri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 12:19:07 by aboukhri          #+#    #+#             */
/*   Updated: 2019/11/22 10:47:58 by aboukhri         ###   ########.fr       */
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

void    history_search(t_history his, char *search)//??
{
    //show search bar in a new line prompt

    //while read by 1 char -> search and reverse mode to the searched charachters 
    //break in enter and execute
}