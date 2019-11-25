/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhri <aboukhri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 14:42:41 by hlamhidr          #+#    #+#             */
/*   Updated: 2019/11/23 17:16:36 by aboukhri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_line.h"

/*
** - function move our cursor to delete the first left character.
** - clear the line from the cursor to the end of screen.
*/

void	ft_move_cursor_fordel(t_cursor *pos)
{
	if (pos->x == 0)
	{
		pos->y--;
		pos->x = pos->end[pos->y];
		ft_movecur_up_and_right(1, pos->x);
	}
	else
	{
		tputs(tgetstr("le", NULL), 0, my_outc);
		pos->x--;
	}
	tputs(tgetstr("cd", NULL), 0, my_outc);
}

/*
** - delete a character from our line first the function remove the character
** from our line, move the cursor in the index 0 and clear the line and print
** it again.
** - reset the cursor in the right position after printing.
** - return our new line.
*/
static void delete_tab()
{
		//char buf[6];
	struct termios original;
	struct termios tattered;
	//char rt;
	/*ft_bzero(buf, 6);
	read(0, buf, 6);
	ft_print_touch_and_join(&g_pos, buf, s);
	(void)s;
	ft_disable();
	
	read(0, buf, 6);
	ft_enable();*/

	tcgetattr(0, &original);
    tattered = original;
    tattered.c_cc[VKILL] = 033;/* New killchar, 033 == ESC. */
    tcsetattr(0, TCSANOW, &tattered);
    /**
     * Simple test to see whether it works.
     */
	ioctl(0, TIOCSTI, "\177");
//    write(1, "Please enter a line: ", 21);
    //rt = read(0, buf, 6);
	//rt = 127;
	//write(1, &rt, 1);
    //ft_print_touch_and_join(&g_pos, buf, s);

    /**
     * Restore original settings.
     */

    tcsetattr(0, TCSANOW, &original);
	//ioctl(0, TIOCSTI, "\12");
}

char	*ft_delcolomn(char *s, t_cursor *pos)
{
	char	*new;
	int		len;
	//int		fd;

	//fd = open("/dev/ttys002", O_WRONLY);
	len = ft_strlen(s);
	pos->num_col = ft_get_size_windz();
	//ft_putchar_fd(s[pos->index - 1], fd);
	if (s[pos->index - 1] == '\t')
	{
		//ft_putendl_fd("tab", fd);
		delete_tab();
	}
	if (pos->index <= len && pos->index > 0)
	{
		if (!(new = ft_memalloc(sizeof(char) * len)))
			return (NULL);
		ft_strncpy(new, s, pos->index - 1);
		ft_strcpy(new + pos->index - 1, s + pos->index);
		ft_move_cursor_fordel(pos);
		ft_putstr_term(pos->num_col, new + pos->index - 1, pos);
		pos->num_lines = ft_get_num_of_lines(pos->num_col, new, pos->p);
		ft_get_end_of_line_pos(pos, new, pos->num_col);
		ft_set_last_position(*pos, pos->num_lines);
		pos->index--;
	}
	else
		return (s);
	free(s);
	return (new);
}
