/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_search.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhri <aboukhri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 16:27:31 by aboukhri          #+#    #+#             */
/*   Updated: 2019/10/12 21:25:20 by aboukhri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/read_line.h"

void    rev_search(t_history his)
{
    int key;
    char *search;
    t_info *res;

    //go to last and print reverse-i-search: 
    search = NULL;
    key = 0;
    while (read(0, &key, 6))
    {
        if (!key_is_char(key))//key is not a char
            return ;
        search = (!search) ? ft_strdup(&key) : ft_strjoir(search, &key, 1);
        if (!(res = history_keyword(his.tail, search, 0)))
            //print search does not match
        else
            
        key = 0;
    }
}

int     key_is_char(int key)
{
    if (key > 0 && key < 128)
        return (1);
    return (0);
}

void    update_search(char *search, char *result)
{
    //1 - clear line 
    ft_move_cursor_zero(g_pos);
	tputs(tgetstr("cd", NULL), 0, my_outc);
    //2 - print result
    ft_putendl(result);
    //3- new line and print search prompt + search
    ft_putstr("bck-i-search: ");
    if (search)
        ft_putstr(search);
    //set underline and reverse mode
    //place cursor in the last match charchter of result
    
}