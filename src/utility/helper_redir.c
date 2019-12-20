/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfetoui <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 18:46:45 by mfetoui           #+#    #+#             */
/*   Updated: 2019/12/14 18:46:48 by mfetoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		reserved_fd(t_redir *st_redirec)
{
	if (!st_redirec)
		return (0);
	if (st_redirec->fd_close == 155 || st_redirec->fd_des == 155 ||
		st_redirec->fd_err == 155 || st_redirec->fd_red == 155)
	{
		print_error("155 is a Reserved file_descriptor", NULL, NULL, 0);
		return (1);
	}
	return (0);
}
