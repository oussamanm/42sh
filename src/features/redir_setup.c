/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_setup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 17:37:00 by onouaman          #+#    #+#             */
/*   Updated: 2019/08/05 17:37:01 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Initiale vrb of rediretion @
*/

void		ft_init_redi(t_redir *st_redir, int type_red)
{
	if (st_redir == NULL)
		return ;
	st_redir->type_red = type_red;
	st_redir->fd_des = -1;
	st_redir->fd_err = -1;
	st_redir->fd_close = -1;
	if (type_red == 1)
		st_redir->fd_red = 1;
	else if (type_red == 0)
		st_redir->fd_red = 0;
	else if (type_red == 2)
		st_redir->fd_red = 1;
	else if (type_red == 3)
		st_redir->fd_red = 0;
	else if (type_red == 4)
		st_redir->fd_red = 0;
	st_redir->fd_file = NULL;
}

/*
** helper function for ft_redi_out (>& || &>) @
*/

void		ft_redi_out_h(t_redir *st_redir, t_tokens *st_tokens)
{
	char *temp;

	temp = NULL;
	if (PREV && PREV->indx == st_tokens->indx && *(st_tokens->value) != '&' &&
		ft_isalldigit(PREV->value))
	{
		PREV->is_arg = 1;
		st_redir->fd_red = ft_atoi(PREV->value);
	}
	temp = get_value_next(NEXT);
	if ((st_tokens->value)[1] == '&' && ft_isalldigit(temp))
		st_redir->fd_des = ft_atoi(temp);
	else
	{
		st_redir->fd_red = 1;
		st_redir->fd_err = 2;
		st_redir->fd_des = -2;
		st_redir->fd_file = temp;
	}
}

/*
** Apply redirection her_doc @
*/

void		ft_apply_hered(t_redir *st_redi)
{
	int fds[2];

	if (st_redi == NULL)
		return ;
	if (pipe(fds) == -1)
		ft_putendl_fd("Error in pipe line of here_doc", 2);
	write(fds[1], st_redi->fd_file, ft_strlen(st_redi->fd_file));
	close(fds[1]);
	st_redi->fd_red = 0;
	st_redi->fd_des = fds[0];
}

/*
** Apply here_doc if exist @
*/

void		ft_apply_her_doc(t_jobctr *st_jobctr)
{
	t_logopr	*st_logopr;
	t_pipes		*st_pipe;
	t_tokens	*st_temp;

	if (!st_jobctr)
		return ;
	while (st_jobctr && (st_logopr = st_jobctr->st_logopr))
	{
		while (st_logopr && (st_pipe = st_logopr->st_pipes))
		{
			while (st_pipe && (st_temp = st_pipe->st_tokens))
			{
				while (st_temp)
				{
					if (st_temp->token == T_RED_HER_D &&
						(st_pipe->st_redir = ft_new_redir()))
						ft_redi_her(st_pipe->st_redir, st_temp);
					st_temp = st_temp->next;
				}
				st_pipe = st_pipe->next;
			}
			st_logopr = st_logopr->next;
		}
		st_jobctr = st_jobctr->next;
	}
}

/*
**	get next value : helper function to get value next of redirection @
*/

char		*get_value_next(t_tokens *st_token)
{
	int	index;
	char *str_rtn;

	if (!st_token)
		return (NULL);
	str_rtn = ft_strdup(st_token->value);
	st_token->is_arg = 1;
	index = st_token->indx;
	st_token = st_token->next;
	while (st_token && CHECK_TOKEN(st_token->token, T_TXT, T_QUO, T_DQUO))
	{
		if (st_token->indx != index)
			break ;
		str_rtn = ft_strjoir(str_rtn, st_token->value, 1);
		st_token->is_arg = 1;
		st_token = st_token->next;
	}
	return (str_rtn);
}