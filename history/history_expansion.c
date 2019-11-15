/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhri <aboukhri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 16:21:54 by aboukhri          #+#    #+#             */
/*   Updated: 2019/11/13 16:12:37 by aboukhri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/read_line.h"


/* call history cmd by ! key */
char    *history_expanssion(t_history *his, char *keyword)
{
    int index;
    char *value;

    if (keyword[0] == '!' && ft_strlen(keyword) == 1 && his->tail)
        return (ft_strdup(his->tail->cmd));
    else if (ft_isalpha(keyword[0]))
        return (ft_strdup(history_keyword(his->tail, keyword, 0)->cmd));
    else if (ft_isdigit(keyword[0]))
        return (history_value(his, keyword, ft_atoi(keyword)));
    else if (keyword[0] == '-' && ft_isdigit(keyword[1]))
    {
        index = his->len + 1 - ft_atoi(keyword + 1);
        return (history_value(his, keyword + 1, index));
    }
    return (NULL);
}

static  char    *parse_history(char *keyword)
{
    int i;

    i = -1;
    while (keyword[++i])
    {
        if (!ft_isdigit(keyword))
            return (keyword + i);
    }
    return (NULL);
}

/* get the value of history index given with their completion*/
char    *history_value(t_history *his, char *keyword, int index)
{
    t_info  *last;
    char    *plus;
    char    *value;

    last = (his->len - index < index - 1) ? his->tail : his->head;
    if (!(last = history_index(last, index, his->len)))
        return (NULL);
    value = last->cmd;
    if ((plus = parse_history(keyword)))
        value = ft_strjoir(value, plus, 1);
    return (value);
}