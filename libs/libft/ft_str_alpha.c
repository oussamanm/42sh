/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_alpha.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhri <aboukhri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 00:45:32 by aboukhri          #+#    #+#             */
/*   Updated: 2019/11/15 00:50:02 by aboukhri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_str_alpha(char *str)
{
    int i;

    i = -1;
    while (str[++i])
    {
        if (!ft_isalpha(str[i]))
            return (0);
    }
    return (1);
}