/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha_exist.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhri <aboukhri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 05:37:58 by aboukhri          #+#    #+#             */
/*   Updated: 2019/11/18 05:42:18 by aboukhri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int     ft_isalpha_exist(char *str)
{
    int i;

    i = -1;
    while (str[++i])
    {
        if (ft_isalpha(str[i]))
            return (1);
    }
    return (0);
}