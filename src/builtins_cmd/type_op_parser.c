/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_options.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 12:17:53 by mfilahi           #+#    #+#             */
/*   Updated: 2019/09/25 12:17:55 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int  a_op(char ch, int flag)
{
	if (ch == 'a' && (flag == (t_flg | maj_p_flg))) //
		flag = (t_flg | maj_p_flg);
	else if (ch == 'a' && (flag & t_flg))
		flag = (a_flg | t_flg);
	else if (ch == 'a' && (flag & p_flg))
		flag = a_flg | p_flg;
	else if (ch == 'a' && (flag & maj_p_flg))
		flag = 0 | maj_p_flg;
	else if (ch == 'a')
		flag = 0 | a_flg;
	return (flag);
}

int  p_op(char ch, int flag)
{
	if (ch == 'p' && (flag & maj_p_flg))
		flag = 0 | maj_p_flg;
	else if (ch == 'p' && (flag & a_flg))
		flag = a_flg | p_flg;
	else if (ch == 'p')
		flag = 0 | p_flg;
	return (flag);
}

int  maj_p_op(char ch, int flag)
{
	if (ch == 'P' && (flag == (a_flg | p_flg)))
		flag = (a_flg | p_flg);
	else if (ch == 'P')
		flag = 0 | maj_p_flg;
	return (flag);
}

int t_op(char ch, int flag)
{
	if (ch == 't' && (flag & a_flg))
		flag = (a_flg | t_flg);
	else if (ch == 't' && (flag & maj_p_flg))
		flag = (t_flg | maj_p_flg);
	else if (ch == 't')
		flag = 0 | t_flg;
	return (flag);
}


int t_fake_option(char *str, int *j)
{
	*j = 0;
	while (*++str && ++*j)
		if (!(*str == 'a'||\
		  	*str == 'p' ||\
			*str == 't' ||\
            *str == 'P' ||\
            *str == 'f'))
			return (1);
	return (0);
}