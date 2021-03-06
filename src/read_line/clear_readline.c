/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_readline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhri <aboukhri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 22:52:04 by hlamhidr          #+#    #+#             */
/*   Updated: 2019/11/16 03:47:27 by aboukhri         ###   ########.fr       */
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
	save_address(&select);
	ft_strdel(&select->save);
	(select != NULL) ? free(select) : 0;
}
