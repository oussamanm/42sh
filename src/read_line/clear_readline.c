/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_readline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlamhidr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 22:52:04 by hlamhidr          #+#    #+#             */
/*   Updated: 2019/08/03 22:52:09 by hlamhidr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_line.h"

/*
** - function free the structs of the historys and selections when we exit
** from our shell
*/

void	ft_clear_readline_struct(void)
{
	t_history	*his;
	t_select	*select;

	his = NULL;
	select = NULL;
	ft_save_address(&his, &select);
	ft_strdel(&select->save);
	ft_free_tab(his->history);
	ft_strdel(&his->path);
	(his != NULL) ? free(his) : 0;
	(select != NULL) ? free(select) : 0;
}
