/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhri <aboukhri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 16:21:54 by aboukhri          #+#    #+#             */
/*   Updated: 2019/11/23 11:50:08 by aboukhri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/read_line.h"

/* get the value of history index given with their completion*/
static  char    *history_expansion_value(t_history his, char *keyword, int index)
{
    t_info  *last;
    char    *plus;
    char    *value;

    last = (his.len - index < index - 1) ? his.tail : his.head;
    if (!(last = history_index(last, index, his.len)))
        return (NULL);
    value = ft_strdup(last->cmd);
    if ((plus = str_notnumber(keyword)))
        value = ft_strjoir(value, plus, 1);
    return (value);
}

static  char    *shift_expansion(char *keyword, int *i)
{
    int bg;

    *i += 1;
    bg = *i;
    while (keyword[*i] && keyword[*i] != '!' && !is_shell_delimiter(keyword[*i]))
        *i += 1;
    return (ft_strsub(keyword, bg, *i - bg));
}

/* get expansions one by one and return false if no expansion left */
static  int    get_next_expansion(char *keyword, char **exp, int *i)
{
    while (keyword[*i] && keyword[*i] != '!' && !is_shell_delimiter(keyword[*i]))
        *i += 1;
    if (!keyword[*i])
        return (0);
    else if (is_shell_delimiter(keyword[*i]))
    {
        *exp = get_delimiter(keyword + *i);
        *i += ft_strlen(*exp);
    }
    else if (keyword[*i + 1] == '!')
    {
        *exp = ft_strdup("!");
        *i += 2;
    }
    else if (ft_isprint(keyword[*i + 1]))
        *exp = shift_expansion(keyword, i);
    if (!keyword[*i] && !*exp)
        return (0);
    return (1);
}

static char     *command_expansion(t_history his, char *exp)
{
    int index;
    t_info *res;

    if (!exp)
        return (NULL);
    if (is_shell_delimiter(exp[0]))
        return (ft_strdup(exp));
    if (exp[0] == '!' && his.tail)
        return (ft_strdup(his.tail->cmd));
    else if (ft_isdigit(exp[0]))
        return (history_expansion_value(his, exp, ft_atoi(exp)));
    else if (exp[0] == '-' && ft_isdigit(exp[1]))
    {
        index = his.len + 1 - ft_atoi(exp + 1);
        return (history_expansion_value(his, exp + 1, index));
    }
    else if (exp[0] && ft_isprint(exp[0]) && (res = history_keyword(his.tail, exp, 0)))
        return (ft_strdup(res->cmd));
    return (NULL);
}

/* get history cmds by ! expansion keyword */
char    *history_expansion(t_history his, char *keyword)
{
    char *exp;
    char *cmd;
    int i;

    cmd = ft_strnew(1);
    if (!his.head || !his.tail || !keyword)
        return (cmd);
    exp = NULL;
    i = 0;
    while (get_next_expansion(keyword, &exp, &i))
    {
        if (!(cmd = ft_strjoir(cmd, command_expansion(his, exp), 3)))
            break ;
        ft_strdel(&exp);
    }
    if (!cmd)
    {
        ft_putstr_fd("42sh: !", 2);
        ft_putstr_fd(exp, 2);
        ft_putendl_fd(": event not found", 2);
    }
    if (exp)
        free(exp);
    return (cmd);
}