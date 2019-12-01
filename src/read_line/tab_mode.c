/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_mode.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhri <aboukhri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 09:16:46 by aboukhri          #+#    #+#             */
/*   Updated: 2019/12/01 18:59:48 by aboukhri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_line.h"

void    convert_neg_to_tab(char **s)
{
    int i;

    if (!s || !*s)
        return ;
    i = -1;
    while (s[0][++i])
    {
        if (s[0][i] < 0)
            s[0][i] = '\t';
    }
}

void   convert_tab_to_neg(char **s)
{
    int i;

    if (!s || !*s)
        return ;
    i = -1;
    while (s[0][++i])
    {
        if (s[0][i] == '\t')
            s[0][i] = -1;
    }
}

void    update_tab_str(char **s, t_cursor *pos)
{
    int x;
    int y;
    int i;
    int sp;

    x = pos->p;
    y = 0;
    i = -1;
    while (s[0][++i])
    {
        if (s[0][i] < 0)
        {
            sp = 8 - (x % 8);
            s[0][i] = sp * -1;
            if (x + sp > pos->end[y])
            {
                x = 0;
                y++;
            }
            else
                x += sp;
        }
        else
        {
            if (x == pos->end[y])
            {
                x = 0;
                y++;
            }
            else
                x++;
        }
    }
}