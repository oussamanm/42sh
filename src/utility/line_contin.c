/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_contin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 10:51:44 by onouaman          #+#    #+#             */
/*   Updated: 2019/12/02 10:51:48 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int				increase_maps(char **maps)
{
	char	*new_buff;
	int		len;

	if (!maps || !(*maps))
		return (-1);
	len = ft_strlen(*maps) + MAX_MAPS;
	if ((new_buff = ft_strnew(len)) == NULL)
		ft_putendl_fd("Error to allocate new area", 2);
	ft_strcpy(new_buff, *maps);
	ft_strdel(maps);
	if ((*maps = new_buff) == NULL)
		return (-1);
	return (len);
}

int				correct_maps_(char *maps, int i, int *quoted, int *rtn)
{
	int temp;

	temp = 0;
	if (MATCH_CLOSED(maps[i], maps[i + 1]) && ++(*rtn))
		bchar(&maps[i], 2, -1);
	else if (maps[i] == 'Q')
	{
		if (!quoted[1])
		{
			temp = count_key(&maps[i + 1], 'q');
			temp = (temp == 0) ? closed_dquot(&maps[i + 1]) : temp;
		}
		quoted[1] = (quoted[1]) ? 0 : 1;
	}
	else if (maps[i] == 'q' && !quoted[1])
	{
		if ((temp = find_flag(&maps[i + 1], 'q')) == -1)
			temp = (!quoted[0]) ? get_last_flag(&maps[i]) : temp;
		quoted[0] = (quoted[0]) ? 0 : 1;
	}
	else if (maps[i] == 'S')
		ft_bzero(quoted, sizeof(int) * 2);
	return (temp);
}

int				fill_maps_h(char *str_cmd, char **maps, int quoted, int j)
{
	int i;

	i = 0;
	if (str_cmd[i] == '\\' && (str_cmd[i + 1] != '\'' || quoted == 0 || !j))
		i += (str_cmd[i + 1]) ? 1 : 0;
	else if (str_cmd[i] == '"')
		(*maps)[j++] = 'Q';
	else if (str_cmd[i] == '\'')
	{
		quoted = (quoted) ? 0 : 1;
		(*maps)[j++] = 'q';
	}
	else if (M_SUBSH(str_cmd[i]) && str_cmd[i + 1] == '(' && ++i)
		(*maps)[j++] = 'S';
	else if (str_cmd[i] == ')')
		(*maps)[j++] = 's';
	return (j);
}
