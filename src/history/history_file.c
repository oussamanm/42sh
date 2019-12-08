/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhri <aboukhri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 15:11:40 by aboukhri          #+#    #+#             */
/*   Updated: 2019/12/07 17:10:35 by aboukhri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_line.h"
#include "shell.h"

/*
**	initialize pointers to NULL
*/

void	init_history(t_history *history)
{
	history->head = NULL;
	history->tail = NULL;
	history->home = NULL;
	history->len = 0;
	history->bg = 1;
}

/*
**	set new env var if not exist
**	EDIT TEXT of fc commad is vim by default
*/

void	init_fc_built(void)
{
	add_intern_var(&g_intern, "FCEDIT", "vim", 0);
}

/*
**	restore history in the begining of program
*/

void	restore_history(t_history *history)
{
	char	*line;
	int		fd;
	char	*home;

	init_history(history);
	if (!(home = ft_get_vrb("HOME", g_environ)))
		return ;
	home = ft_strjoir(ft_strjoir(home, "/", 1), ".42sh_history", 1);
	history->home = home;
	if ((fd = open(history->home, O_RDONLY | O_CREAT, 00600)) == -1)
		return ;
	line = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		insert_history(history, line);
		ft_strdel(&line);
	}
	history->bg = history->len + 1;
	close(fd);
}

/*
**	save the inserted commands in the current session bfore
*/

void	save_history(t_history *history)
{
	t_info	*lst;
	int		fd;

	if (!history || !history->head || !history->tail || !history->home)
		return ;
	if ((fd = open(history->home, O_WRONLY | O_APPEND
					| O_CREAT, 00600)) == -1)
		return ;
	lst = (history->len - history->bg < history->bg - 1) ?
		history->tail : history->head;
	if (!(lst = history_index(lst, history->bg, history->len)))
		return ;
	while (lst)
	{
		write(fd, lst->cmd, ft_strlen(lst->cmd));
		write(fd, "\n", 1);
		lst = lst->next;
	}
	close(fd);
}
