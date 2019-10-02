#include "shell.h"

void    no_options(char *arg, int *flag)
{
    char *path;

    path = NULL;
    if (is_builtin(arg))
        buil_putstr(arg, " is a shell builtin", NULL, 1);
    else if ((path = ft_find_path(arg,  g_environ)))
        buil_putstr(arg, " is ", path, 1);
    else if ((*flag = 1))
        buil_putstr("42sh: type ", arg, ": not found", 2);
    ft_strdel(&path);
}

void    a_option(char *arg)
{
    char *path;

    path = NULL;
    if (is_builtin(arg))
        buil_putstr(arg, " is a shell builtin", NULL, 1);
    if ((path = ft_find_path(arg,  g_environ)))
        buil_putstr(arg, " is ", path, 1);
}

void   p_option(char *arg, int maj_p)
{
    char *path;

    path = NULL;
    if ((path = ft_find_path(arg,  g_environ)) && !is_builtin(arg))
        buil_putstr(path, NULL, NULL, 1);
    else if ((path = ft_find_path(arg,  g_environ)) && is_builtin(arg) && maj_p)
        buil_putstr(path, NULL, NULL, 1);
    ft_strdel(&path);
}


void    t_option(char *arg, int flag)
{
    char *path;

    path = NULL;
    if (is_builtin(arg) && flag)
        buil_putstr("builtin", NULL, NULL, 1);
    else if ((path = ft_find_path(arg,  g_environ)))
        buil_putstr("file", NULL, NULL, 1);
    ft_strdel(&path);
}


void    at_option(char *arg)
{
    char *path;

    path = NULL;
    if (is_builtin(arg))
        buil_putstr("builtin", NULL, NULL, 1);
    if ((path = ft_find_path(arg,  g_environ)))
        buil_putstr("file", NULL, NULL, 1);
    ft_strdel(&path);
}