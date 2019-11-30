/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhri <aboukhri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 15:16:21 by aboukhri          #+#    #+#             */
/*   Updated: 2019/11/30 19:06:48 by aboukhri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/read_line.h"

/*
**	get history command by taking the shortcut starting from head
**	or tail acording to index
*/

t_info	*history_value(t_history his, char *keyword)
{
	int		index;
	t_info	*ptr;

	if (!keyword)
		return (NULL);
	if (ft_isdigit(keyword[0]))
	{
		index = ft_atoi(keyword);
		ptr = (his.len - index < index) ? his.tail : his.head;
		return (history_index(ptr, index, his.len));
	}
	return (history_keyword(his.tail, keyword, 0));
}

/*
**	get history command by keyword given
**	in the direction given (1 -> next | 0 -> prev)
*/

t_info	*history_keyword(t_info *history, char *keyword, int dir)
{
	t_info	*lst;
	int		len;

	if (!keyword)
		return (NULL);
	len = ft_strlen(keyword);
	lst = history;
	while (lst)
	{
		if (ft_strncmp(keyword, lst->cmd, len) == 0)
			return (lst);
		lst = (dir) ? lst->next : lst->prev;
	}
	return (NULL);
}

/*
**	get history command by index given in case not found return NULL
*/

t_info	*history_index(t_info *history, int index, int len)
{
	t_info	*lst;

	if (index < 1 || index > len)
		return (NULL);
	lst = history;
	while (lst)
	{
		if (lst->index == index)
			return (lst);
		lst = (lst->index > index) ? lst->prev : lst->next;
	}
	return (NULL);
}

t_info	*new_history(int index, char *cmd, t_info *prev)
{
	t_info	*new;

	if (!(new = (t_info*)malloc(sizeof(t_info))))
		return (NULL);
	new->index = index;
	new->cmd = ft_strdup(cmd);
	new->next = NULL;
	new->prev = prev;
	return (new);
}

void	insert_history(t_history *history, char *cmd)
{
	if (!history->head)
	{
		history->head = new_history(1, cmd, NULL);
		history->tail = history->head;
	}
	else
	{
		history->tail->next = new_history(history->tail->index + 1,
				cmd, history->tail);
		history->tail = history->tail->next;
	}
	history->len++;
}
