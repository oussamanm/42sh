/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_search.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhri <aboukhri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 12:19:07 by aboukhri          #+#    #+#             */
/*   Updated: 2019/11/29 00:11:22 by aboukhri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/read_line.h"


void	his_cursor_do(t_cursor pos, int nbr)//??
{
	//int fd = open("/dev/ttys001", O_WRONLY);
	//dprintf(fd, "nbr: %d\n", nbr);
	while (nbr-- > 0)
		tputs(tgetstr("do", NULL), 0, my_outc);
	tputs(tgoto(tgetstr("ch", NULL), 0, pos.x), 0, my_outc);//??
}


void	his_cursor_up(t_cursor pos, int nbr)//??
{
	int y;

	y = nbr;
	//ft_move_left(pos.x);
	while (y-- > 0)
		tputs(tgetstr("up", NULL), 0, my_outc);
	//ft_move_right(pos.p);
	tputs(tgoto(tgetstr("ch", NULL), 0, pos.p), 0, my_outc);//??
}

void	his_putstr_term(int num_col, char *s, char *str, t_cursor *pos)
{
	int i;

	int x;
    int bl;
    int j;
//int fd = open("/dev/ttys006", O_WRONLY);
	i = 0;
	x = pos->x;
    j = 0;
    bl = 0;
	//dprintf(fd, "begin\n");
	while (s[i])
	{
        if (j != -1 && str[j] == s[i])
            j++;
        else if (j > 0 && str[i] != s[i])
            j = -1;
		if (s[i] < 0)
		{
			//dprintf(fd, "put : %d | num_col: %d\n", s[i], num_col);
			print_tab(s[i] * -1, num_col, &x);
		}
		else
		{
            if (j > 0)
                tputs(tgetstr("us", NULL), 0, my_outc);
            else if (j == -1)
                tputs(tgetstr("ue", NULL), 0, my_outc);
			ft_putchar(s[i]);
			if (x == num_col - 1 || s[i] == '\n')
			{
				if (x == num_col - 1 && s[i] != '\n')
					tputs(tgetstr("do", NULL), 0, my_outc);
				x = 0;
			}
			else
				x++;
		}
		i++;
	}
    tputs(tgetstr("ue", NULL), 0, my_outc);
}

void	search_new_line(char *search, char *line, char **cmd, t_cursor *pos)
{
	//his_cursor_zero(*pos);
    pos->x = 8;
	pos->y = 0;
	tputs(tgetstr("cd", NULL), 0, my_outc);
	his_putstr_term(pos->num_col, line, search, pos);
	ft_get_end_of_line_pos(pos, line, pos->num_col);
	pos->num_lines = ft_get_num_of_lines(pos->num_col, line, pos->p);
	pos->index = ft_strlen(line);
	pos->x = pos->end[pos->num_lines - 1];
	pos->y = pos->num_lines - 1;
	*cmd = ft_strdup(line);
}

static char *history_strstr(t_info *last, char *search)
{
    while (last)
    {
        if (ft_strstr(last->cmd, search))
            return (ft_strdup(last->cmd));
        last = last->prev;
    }
    return (NULL);
}

 void reset_search(char **cmd)
{
   // his_new_line(*cmd, cmd, &g_pos);
    tputs(tgetstr("cd", NULL), 0, my_outc);
    ft_initial(8);
    ft_get_end_of_line_pos(&g_pos, *cmd, g_pos.num_col);
    ft_putstr_term(g_pos.num_col, *cmd, &g_pos);
	g_pos.num_lines = ft_get_num_of_lines(g_pos.num_col, *cmd, g_pos.p);
    his_cursor_up(g_pos, g_pos.num_lines - 1);
	g_pos.index = 0;
	g_pos.x = g_pos.p;
	g_pos.y = 0;
//     tputs(tgetstr("cd", NULL), 0, my_outc);
//     ft_initial(8);
//     g_pos.num_lines = ft_get_num_of_lines(g_pos.num_col, cmd, g_pos.p);
//     ft_putstr_term(g_pos.num_col, cmd, &g_pos);
//    // g_pos.num_lines = ft_get_num_of_lines(g_pos.num_col, cmd, g_pos.p);
//     his_cursor_up(g_pos, g_pos.num_lines - 1);
    /*g_pos.x = 8;
    g_pos.y = 0;
    ft_putstr_term(g_pos.num_col, cmd, &g_pos);
    ft_get_end_of_line_pos(&g_pos, cmd, g_pos.num_col);
    g_pos.num_lines = ft_get_num_of_lines(g_pos.num_col, cmd, g_pos.p);
    g_pos.x = 8;
    g_pos.y = 0;
    his_cursor_up(g_pos, g_pos.num_lines - 1);*/
    //tputs(tgoto(tgetstr("ch", NULL), 0, g_pos.p), 0, my_outc);
    //get back to the position
}

static void his_edit_line(char *search, char *res, char **cmd)
{
    int down;
    int up;
    int p;
    
    p = 14;
    up = ft_strlen(search);
    if (cmd && *cmd)
        g_pos.num_lines = ft_get_num_of_lines(g_pos.num_col, *cmd, g_pos.p);
    if (res && search)
    {
        search_new_line(search, res, cmd, &g_pos); 
        down = 1;
    }
    else if (search)
        down = g_pos.num_lines;
    else
        down = g_pos.num_lines - g_pos.y;
    
    
    his_cursor_do(g_pos, down);
    //tputs(tgetstr("do", NULL), 0, my_outc);
    tputs(tgoto(tgetstr("ch", NULL), 0, 0), 0, my_outc);
    tputs(tgetstr("cd", NULL), 0, my_outc);
    if (!res && up > 0)
    {
        ft_putstr("failing ");//8
        p += 8;
    }
    ft_putstr("bck-i-search: ");//15
    ft_putstr(search);
    tputs(tgetstr("us", NULL), 0, my_outc);
    ft_putchar(' ');
    up = g_pos.num_lines + ((up + p) / g_pos.num_col);
    tputs(tgetstr("ue", NULL), 0, my_outc);
    his_cursor_up(g_pos, up);
   // tputs(tgetstr("up", NULL), 0, my_outc);
    
    
    ft_get_end_of_line_pos(&g_pos, *cmd, g_pos.num_col);

    //ft_set_last_position(g_pos, g_pos.num_lines);
    //move cursor to the first chachter in search
}//ft_set_last_position(*pos, pos->num_lines); must be in the end of line  ft_get_end_of_line_pos(pos, s, pos->num_col);

int    history_search(t_history his, char **s)//??
{
    char buff[6];
    char *search;
    char *res;
    int len;

    //int fd = open("/dev/ttys007", O_WRONLY);
    his_edit_line(NULL, NULL, s);
    ft_bzero(buff, 6);
    res = NULL;
    search = ft_strnew(1);
    while (read(0, buff, 5))
    {
        len = ft_strlen(search);
        if (DEL == CAST(buff))
            (len > 0) && (search[--len] = '\0');
        else if (ft_isallprint(buff))
        {
            search = ft_strjoir(search, buff, 1);
            len++;
        }
        else
        {
            reset_search(s);
            return (CAST(buff));
        }
       // dprintf(fd, "|search: %s|\n", search);
        if (len == 0)
            res = ft_strnew(1);
        else if (len > 0)
            res = history_strstr(his.tail, search);
        his_edit_line(search, res, s);
        ft_bzero(buff, 6);
        ft_strdel(&res);
    }
    return (0);
}