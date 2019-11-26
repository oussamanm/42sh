/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_mem.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhri <aboukhri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 12:43:20 by aboukhri          #+#    #+#             */
/*   Updated: 2019/11/26 15:44:06 by aboukhri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	garbage_mem(void *mem, t_garbage **grb)
{
	t_garbage	*new;

	if (!(new = (t_garbage*)malloc(sizeof(t_garbage))))
		return ;
	new->mem_ptr = mem;
	new->next = NULL;
	if (!(*grb))
	{
		(*grb) = new;
		(*grb)->tail = (*grb);
	}
	else
	{
		(*grb)->tail->next = new;
		(*grb)->tail = (*grb)->tail->next;
	}
}
