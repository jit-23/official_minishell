/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eescalei <eescalei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 22:03:12 by eescalei          #+#    #+#             */
/*   Updated: 2024/07/30 04:25:28 by eescalei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*next_run(t_token *token, int skip)
{
	if (token && skip)
		token = token->next;
	while (token && token->type != _EXEC && token->next)
	{
		token = token->next;
		if (token && token->type == _EXEC && token->prev == NULL)
			;
		else if (token && token->type == _EXEC && token->next/* && token->prev->type < _END */)
			token = token->next;
	}
	return (token);
}