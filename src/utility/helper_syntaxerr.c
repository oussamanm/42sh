/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_syntaxerr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 19:11:21 by onouaman          #+#    #+#             */
/*   Updated: 2019/12/07 19:11:24 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** check syntax error token redirection
*/

int			error_token_redi(t_tokens *st_tokens)
{
	if (NEXT && T_IS_TXT(NEXT->token))
		return (0);
	else if (!NEXT && !M_CHECK(TOKEN, T_RED_IN_B, T_RED_OUT_B))
		return (1);
	else if (NEXT && !T_IS_SUBSHELL(NEXT->token) &&
		!M_CHECK(TOKEN, T_RED_IN_B, T_RED_OUT_B))
		return (1);
	return (0);
}
