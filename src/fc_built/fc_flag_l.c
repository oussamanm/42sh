/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_flag_l.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhri <aboukhri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 00:09:35 by aboukhri          #+#    #+#             */
/*   Updated: 2019/12/08 17:00:04 by aboukhri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_line.h"
#include "shell.h"

t_info			*fc_value(t_history his, char *key)
{
	int		index;
	t_info	*ptr;

	if (ft_isdigit(key[0]) || (key[0] == '-' && ft_isdigit(key[1])))
	{
		index = ft_atoi(key);
		if (index > his.len)
			index = his.len;
		if (index <= 0)
			index = his.len + index;
		ptr = (his.len - index < index) ? his.tail : his.head;
		return (history_index(ptr, index, his.len));
	}
	return (history_keyword(his.tail, key, 0));
}

static	void	fc_l_list(t_history *lst, t_history his, char *from, char *to)
{
	int			jk;

	init_history(lst);
	if (!his.head || !his.tail)
		return ;
	if (from)
		lst->head = fc_value(his, from);
	else
	{
		jk = (his.len > 15) ? his.len - 15 : his.head->index;
		lst->head = history_index(his.tail, jk, his.len);
	}
	if (to)
		lst->tail = fc_value(his, to);
	else
		lst->tail = his.tail;
}

/*
**	show list from index depends on the the arguments given
*/

int				fc_flag_l(t_history history, unsigned char flags, char **args)
{
	t_history	lst;
	int			len;
	char		*from;
	char		*to;

	len = ft_strrlen(args);
	from = (len > 0) ? args[0] : NULL;
	to = (len > 1) ? args[1] : NULL;
	fc_l_list(&lst, history, from, to);
	if (!lst.head || !lst.tail)
	{
		ft_putendl_fd("42sh: fc: history specification out of range", 2);
		return (EXIT_FAILURE);
	}
	if (flags & FC_R)
		rev_his_list(&lst);
	if (flags & FC_N)
		display_his_list(lst, 0);
	else
		display_his_list(lst, 1);
	return (EXIT_SUCCESS);
}
