/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhri <aboukhri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 23:42:10 by onouaman          #+#    #+#             */
/*   Updated: 2019/12/02 06:41:46 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "read_line.h"

/*
** Execute all cmds
*/

static void		ft_cmds_exec(t_cmds *st_cmds)
{
	t_jobctr	*st_jobctr;

	if (!st_cmds)
		return ;
	st_jobctr = st_cmds->st_jobctr;
	while (st_jobctr)
	{
		logical_ops(st_jobctr->st_logopr);
		st_jobctr = st_jobctr->next;
	}
}

/*
** Execute of Cmd
*/

static void		ft_cmd_exec(char **args, char **env)
{
	char	*str_arg;

	str_arg = NULL;
	if (!args || !args[0])
		exit(EXIT_SUCCESS);
	if (ft_check_char(args[0], '/'))
		str_arg = args[0];
	else
	{
		if (!(str_arg = lookup_hash(args[0])))
			str_arg = ft_find_path(args[0], env);
	}
	if (str_arg != NULL)
	{
		execve(str_arg, args, env);
		ft_strdel(&str_arg);
	}
	exit(EXIT_FAILURE);
}

/*
** Handle child process by , call redirection and call function execution
*/

void			ft_handle_child(t_pipes *st_pipes, char **environ)
{
	ft_signal_default();
	if (g_proc_sub && st_pipes->bl_jobctr)
	{
		dup2(open("/dev/null", O_RDONLY), 0);
		if (g_proc_sub == 1)
			signal(SIGINT, SIG_IGN);
	}
	if (ft_check_redi(st_pipes) && parse_redir(st_pipes) == PARSE_KO)
		exit(EXIT_FAILURE);
	if (lookup_hash(st_pipes->args[0]))
		ft_cmd_exec(st_pipes->args, environ);
	else if (!ft_check_cmd(st_pipes->args[0], environ))
		ft_cmd_exec(st_pipes->args, environ);
	else
		exit(EXIT_CMD_NF);
}

/*
** Create child proc, check built, call for apply redirect , Execution
*/

int				ft_cmd_fork(int fork_it, t_pipes *st_pipes)
{
	int		pid;
	int		rtn;
	char	**environ;

	pid = 0;
	rtn = 0;
	if (!st_pipes || !st_pipes->st_tokens)
		return (0);
	remove_backslashs(st_pipes->st_tokens);
	tokens_to_args(st_pipes);
	environ = (st_pipes->tmp_env) ? st_pipes->tmp_env : g_environ;
	if (st_pipes->args && ft_check_built(*(st_pipes->args)))
		return (ft_init_built(st_pipes, fork_it, &environ));
	(fork_it) ? signal(SIGCHLD, SIG_DFL) : 0;
	(fork_it && (pid = fork()) == -1) ? ft_err_exit(ERR_FORK) : 0;
	if (pid > 0 && fork_it && !g_proc_sub)
		ft_manage_jobs(pid, st_pipes, &rtn);
	if (pid == 0)
		ft_handle_child(st_pipes, environ);
	else if (fork_it && g_proc_sub && !st_pipes->bl_jobctr)
		waitpid(pid, &rtn, 0);
	(fork_it) ? signal(SIGCHLD, ft_catch_sigchild) : 0;
	if (rtn == EXIT_SUCCESS && st_pipes->args)
		insert_hash(*st_pipes->args, ft_find_path(*st_pipes->args, environ));
	return (rtn);
}

int			ft_lstfind(t_list *st_list, char *content)
{
	if (!st_list)
		return (0);
	while (st_list)
	{
		dprintf(2, "++ Compare %s , %s \n",st_list->content,content);
		if (STR_CMP(st_list->content, content))
			return (1);
		st_list = st_list->next;
	}
	return (0);
}

t_tokens	*get_last_token(t_tokens *st_tokens)
{
	if (!st_tokens)
		return (NULL);
	while (st_tokens)
	{
		if (NEXT == NULL)
			break ;
		st_tokens = NEXT;
	}
	return (st_tokens);
}

t_tokens		*handle_value_alias(char *value, t_tokens *st_tokens, t_tokens **st_head)
{
	t_tokens	*st_token;
	t_tokens	*last_token;
	char		**args;
	t_tokens	*st_prev;
	t_tokens	*st_next;

	dprintf(2,"**** Entred to handle_value with value=|%s| and st_token=|%s| and st_head=|%s| \n", value,st_tokens->value,(*st_head)->value);

	if (!value || !st_tokens)
		return (st_tokens);
	args = ft_str_split_q(value, " \t\n");
	st_token = ft_lexer(args);
	ft_strrdel(args);
	if (!st_token)
		return (st_tokens);
	st_prev = st_tokens->prev;
	st_next = st_tokens->next;
	last_token = get_last_token(st_token);
	if (st_prev == NULL)
	{
		dprintf(2,"*** head become st_token=|%s| \n", (*st_head)->value);
		*st_head = st_token;
	}
	else
	{
		st_prev->next = st_token;
		st_token->prev = st_prev;
	}
	if (st_next)
		st_next->prev = last_token;
	if (last_token)
		last_token->next = st_next;
	sleep(3);
	return (st_token);
}

char				*get_value_alias(char *key)
{
	t_aliaspkg	*data;
	t_alias		*curr;
	char		*temp;
	char		*rtn;

	if (!(data = storeaddrstruct(NULL)))
		return (NULL);
	if (!(curr = data->head_ref))
		return (NULL);
	
	temp = ft_strjoir(key, "=", 0);
	rtn = NULL;
	while (curr)
	{
		if (ft_strcmp(curr->shortcut, temp) == 0)
		{
			rtn = curr->cmd;
			break ;
		}
		curr = curr->next;
	}
	ft_strdel(&temp);
	return (rtn);
}
/*
void				handle_alias(t_tokens **st_head)
{
	t_tokens *st_tokens;
	t_tokens *st_temp;
	int			bl;
	char		*value_alias;

	bl = 0;
	st_temp = NULL;
	value_alias = NULL;
	st_tokens = *st_head;
	while (st_tokens)
	{
		if (st_tokens == *st_head || (OPER_TOKEN(TOKEN) && NEXT && T_IS_TXT(NEXT->token)))
		{
			dprintf(2,"Start with st_tokens=|%s| and HEAD=|%s| \n",st_tokens->value,(*st_head)->value);
			st_temp = (st_tokens == *st_head) ? st_tokens : NEXT;
			/// Check if alias
			if ((value_alias = get_value_alias(st_temp->value)) && ++bl)
			{
				dprintf(2, "-- before handle alias value Entred with = |%s| and value_alias = |%s|\n",st_temp->value,value_alias);
				st_tokens = handle_value_alias(value_alias, st_temp, st_head);
				dprintf(2,"------------ tokens-------------\n");
					t_tokens *temp = *st_head;
					while (temp)
					{
						dprintf(2, "<%d><token = %d> value =|%s|\n",temp->indx, temp->token, temp->value);
						temp = temp->next;
					}
				dprintf(2,"-------	fin ---------\n");				
			}
		}
		if (NEXT == NULL && bl == 1)
		{
			dprintf(2, "************* Reapeat loop ***************\n");
			st_tokens = *st_head;
		}
		st_tokens = NEXT;
	}
}*/

void				handle_alias(t_tokens **st_head)
{
	t_tokens	*st_tokens;
	int			bl = 0;
	char		*value;
	t_list	*st_list;

	st_list = ft_lstnew(NULL,0);
	st_tokens = *st_head;
	value = NULL;
	while (st_tokens)
	{
		if (st_tokens == *st_head)
			bl = 1;
		else if (OPER_TOKEN(TOKEN) && NEXT && T_IS_TXT(NEXT->token))
			bl = 2;
		if (bl || (bl == 0 && T_IS_TXT(st_tokens->token)))
		{
			st_tokens = (bl == 2) ? NEXT : st_tokens;
			if ((value = get_value_alias(st_tokens->value)) && ft_lstfind(st_list, st_tokens->value) == 0) /// not exist in st_list
			{
				dprintf(2,"--->push value=|%s| to list \n", st_tokens->value);
				ft_lstadd(&st_list, ft_lstnew(st_tokens->value, ft_strlen(st_tokens->value) - 1));
				st_tokens = handle_value_alias(value, st_tokens, st_head); /// get the head of token_value_alias

					////
						dprintf(2, "---------- Result after handle and index=|%s| -------------\n",st_tokens->value);
						t_tokens *tmp = *st_head;
						while (tmp)
						{
							sleep(1);
							dprintf(2,"<%d> Tken <%d> value = |%s|\n",tmp->indx, tmp->token, tmp->value);
							tmp = tmp->next;
						}
						dprintf(2, "----- 	fin -----\n");
					////
			}
			bl = 0;
		}
		st_tokens = (st_tokens) ? NEXT : st_tokens;
	}
}

/*
** Config Cmds by : - Lexer - Check Syntax - sub_shell - her_doc - Clear lists
*/

int				ft_cmds_setup(char *str_arg, int bl_subsh)
{
	t_cmds		*st_cmds;

	if (str_arg == NULL)
		return (-1);
	st_cmds = ft_new_cmds();
	st_cmds->args = ft_str_split_q(str_arg, " \t\n");
<<<<<<< HEAD
	st_cmds->st_tokens = ft_lexer(st_cmds->args);
	dprintf(2,"--Begin with st_token=|%s| \n", st_cmds->st_tokens->value);
	handle_alias(&(st_cmds->st_tokens));
	dprintf(2,"--Finished with st_token=|%s| \n", st_cmds->st_tokens->value);
					dprintf(2, "---------- Result after handle -------------\n");
						t_tokens *tmp = st_cmds->st_tokens;
						while (tmp)
						{
							dprintf(2,"<%d> Tken <%d> value = |%s|\n",tmp->indx, tmp->token, tmp->value);
							tmp = tmp->next;
						}
						dprintf(2, "----- 	fin -----\n");
	if (error_syntax_lexer(st_cmds->st_tokens))
=======
	st_cmds->args = aliasmatched(st_cmds->args);
	// int i;
	// i = 0;
	// while (st_cmds->args[i])
	// {
	// 		ft_putstr_fd("ret of aliasmatched ==> ", 1);
	// 		ft_putendl_fd(st_cmds->args[i], 1);
	// 		i++;
	// }
	if ((st_cmds->st_tokens = ft_lexer(st_cmds->args)) == NULL ||
		error_syntax_lexer(st_cmds->st_tokens))
>>>>>>> 3a7373168ef04407d5358d173400e60c44134e2e
	{
		free_list_cmds(st_cmds);
		return ((g_exit_status = 258));
	}
	ft_update_tokens(st_cmds->st_tokens);
	apply_subsh(st_cmds->st_tokens);
	if (ft_check_token(st_cmds->st_tokens, T_PROC_IN) ||
		ft_check_token(st_cmds->st_tokens, T_PROC_OUT))
		proc_substitution(st_cmds);
	ft_parse_cmd(st_cmds);
	(!bl_subsh) ? ft_apply_her_doc(st_cmds->st_jobctr) : NULL;
	(!g_pos.exit) ? ft_cmds_exec(st_cmds) : 0;
	procsub_close(st_cmds->fd);
	free_list_cmds(st_cmds);
	return (0);
}
