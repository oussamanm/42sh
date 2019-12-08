/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_built.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhri <aboukhri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 15:45:42 by aboukhri          #+#    #+#             */
/*   Updated: 2019/12/08 17:31:01 by aboukhri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_line.h"
#include "shell.h"

static	char	*history_getcmds(t_history his, char **args, int r)
{
	int			len;
	char		*content;
	t_history	val;

	len = ft_strrlen(args);
	content = NULL;
	if (!len && his.tail)
		content = ft_strdup(his.tail->cmd);
	else if (len == 1 && (val.head = fc_value(his, args[0])))
		content = ft_strdup(val.head->cmd);
	else if (len > 1)
	{
		val = (t_history){fc_value(his, args[0]),\
		fc_value(his, args[1]), NULL, 0, 0};
		if (r)
			rev_his_list(&val);
		content = history_content(val);
	}
	return (content);
}

/*
**	edit commands given from arguments(index, string)
**	by the editor given and re-execute them
*/

int				fc_edit(t_history his, char *editor,
					unsigned char fl, char **args)
{
	char	*content;
	char	*cmd;

	if (editor == NULL)
	{
		ft_putendl_fd("42sh: must specify editor in FCEDIT", 2);
		return (EXIT_FAILURE);
	}
	(fl && args) && (args++);
	if (!(content = history_getcmds(his, args, (fl & FC_R) ? 1 : 0)))
	{
		ft_putendl_fd("42sh: fc: history specification out of range", 2);
		return (EXIT_FAILURE);
	}
	write_fc(content);
	ft_strdel(&content);
	cmd = ft_strjoin(editor, " .42sh-fc");
	ft_multi_cmd(cmd, 0);
	ft_strdel(&cmd);
	if (g_exit_status != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/*
**	execute commands edited from history
*/

void			exec_fc(void)
{
	char	*content;
	char	**cmds;
	int		i;

	if (!(content = read_fc()))
		return ;
	cmds = ft_strsplit(content, '\n');
	ft_strdel(&content);
	i = -1;
	while (cmds && cmds[++i])
	{
		if (!history_handling(&cmds[i]))
			continue ;
		ft_putendl(cmds[i]);
		ft_multi_cmd(cmds[i], 0);
	}
	ft_strrdel(cmds);
}

int				fc_3adiya(t_history his, unsigned char flags,
							char **args, char **env)
{
	char	*editor;

	if (!(editor = ft_get_vrb("FCEDIT", env)))
		editor = get_intern_value("FCEDIT");
	(!editor) && (editor = ft_strdup("vi"));
	if (fc_edit(his, editor, flags, args))
		return (EXIT_FAILURE);
	ft_strdel(&editor);
	if (access(".42sh-fc", F_OK) == 0)
		ft_multi_cmd("rm .42sh-fc", 0);
	return (EXIT_FAILURE);
}

int				fc_built(char **args, t_history *history, char **env)
{
	unsigned	char	flags;
	char				c;
	int					pos;

	if (!history->head || !history->tail)
	{
		ft_putendl_fd("42sh: fc: history specification out of range", 2);
		return (EXIT_FAILURE);
	}
	if ((pos = read_fc_flags(args, &flags, &c)) == -1)
	{
		fc_usage(c, "invalid option");
		return (EXIT_FAILURE);
	}
	if (flags & FC_S)
		return (fc_flag_s(history, *(args + pos)));
	else if (flags & FC_E)
		return (fc_flag_e(*history, args + pos));
	else if (flags & FC_L)
		return (fc_flag_l(*history, flags, args + pos));
	else if (flags == 0 || flags & FC_R)
		return (fc_3adiya(*history, flags, args, env));
	return (EXIT_SUCCESS);
}
