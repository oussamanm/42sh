/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_content.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhri <aboukhri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 10:51:28 by aboukhri          #+#    #+#             */
/*   Updated: 2019/12/02 11:22:03 by aboukhri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/read_line.h"

/*
**	get history content from head to tail given
**	and return it in a format of string
*/

char			*history_content(t_history his)
{
	t_info	*head;
	char	*content;

	if (!his.head || !his.tail)
		return (NULL);
	content = NULL;
	head = his.head;
	while (head)
	{
		content = (!content) ? ft_strdup(head->cmd) :
					ft_strjoir(content, head->cmd, 1);
		content = ft_strjoir(content, "\n", 1);
		if (his.tail && his.tail->index == head->index)
			break ;
		head = (head->index < his.tail->index) ? head->next : head->prev;
	}
	return (content);
}

static	void	put_nbr_len(int index, int max)
{
	char	*id;
	int		len;
	int		i;

	id = ft_itoa(index);
	len = ft_strlen(id);
	i = -1;
	while (++i < max - len)
		ft_putchar(' ');
	ft_putnbr(index);
}

/*
**	display history withb indexes in case order is true
*/

void			display_his_list(t_history his, int order)
{
	t_info	*lst;
	int		max;
	char	*index;

	lst = his.head;
	if (order)
	{
		index = ft_itoa(g_history.tail->index);
		max = ft_strlen(index);
		ft_strdel(&index);
	}
	while (lst)
	{
		if (order)
			put_nbr_len(lst->index, max);
		ft_putchar('\t');
		ft_putendl(lst->cmd);
		if (lst->index == his.tail->index)
			return ;
		lst = (lst->index > his.tail->index) ? lst->prev : lst->next;
	}
}
