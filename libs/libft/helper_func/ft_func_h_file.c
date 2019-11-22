/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_func_h_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 03:42:03 by onouaman          #+#    #+#             */
/*   Updated: 2019/05/03 06:28:03 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int			ft_find_file(char *path, char *file)
{
	DIR				*dir;
	struct dirent	*dr;
	int				len;

	dir = opendir(path);
	if (access(path, F_OK) != 0 || dir == NULL)
		return (-1);
	len = ft_strlen(file);
	while ((dr = readdir(dir)) != NULL)
	{
		if (len == dr->d_namlen && ft_strcmp(dr->d_name, file) == 1)
		{
			closedir(dir);
			return (1);
		}
	}
	closedir(dir);
	return (0);
}

/*
** Check file if exist and check permission read , write
*/

int			ft_check_file(char *file, int mode)
{
	int			bl;
	struct stat	st_stat;

	mode = (mode == 0) ? R_OK : W_OK;
	bl = 0;
	if (access(file, F_OK) == 0)
	{
		if (lstat(file, &st_stat) == 0 && S_ISDIR(st_stat.st_mode) && ++bl)
			print_error("Is a directory", "42sh :", file, 0);
		else if (access(file, mode) != 0 && ++bl)
			print_error(FIL_PD, "42sh :", file, 0);
	}
	else if ((mode == R_OK || !ft_strlen(file)) && ++bl)
		print_error(FIL_NS, "42sh :", file, 0);
	return (bl);
}

/*
** open file :  type : rd=0, wr=1, app=2, rdwr=3
*/

int			ft_open_file(char *file, int type)
{
	int fd;
	int flag;

	flag = 0;
	if (file == NULL)
	{
		print_error("No such file or directory", "42sh :", " ", 0);
		return (-1);
	}
	fd = -1;
	if (ft_check_file(file, type) == 0)
	{
		if (type == 1)
			flag = type | O_TRUNC;
		else if (type == 0)
			flag = 0;
		else if (type == 2)
			flag = type | O_APPEND;
		else if (type == 3)
			flag = O_RDWR;
		if ((fd = open(file, flag | O_CREAT, 0644)) == -1)
			print_error("Error in open File ", "42sh :", " ", 0);
	}
	return (fd);
}

/*
** Check exist file descriptor
*/

int			ft_exist_fd(int fd)
{
	if (read(fd, NULL, 0) == -1 && write(fd, NULL, 0) == -1)
	{
		print_error("Bad file descriptor", "42sh :", ft_itoa(fd), 2);
		return (0);
	}
	return (1);
}
