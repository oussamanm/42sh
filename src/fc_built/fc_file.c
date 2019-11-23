/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_file.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhri <aboukhri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 00:18:39 by aboukhri          #+#    #+#             */
/*   Updated: 2019/11/23 11:59:50 by aboukhri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/read_line.h"
#include "../../includes/shell.h"

/** fc file management **/
char    *read_fc()
{
    int fd;
    char buff[1001];
    char *cmd;
    int rt;

    cmd = NULL;
    if ((fd = open(".42sh-fc", O_RDONLY, 00600)))
    {
        ft_bzero(buff, 1000);
        while ((rt = read(fd, buff, 1000)) > 0)
        {
            cmd = (!cmd) ? ft_strdup(buff) : ft_strjoir(cmd, buff, 1);
            if (rt == 1000)
                ft_bzero(buff, 1000);
        }
        close(fd);
    }
    return (cmd);
}

/*  write in .42-fc file the content given */
void    write_fc(char *content)
{
    int fd;

    if ((fd = open(".42sh-fc", O_WRONLY | O_TRUNC | O_CREAT, 00600)))
    {
        ft_putendl_fd(content, fd);
        close(fd);
    }
}