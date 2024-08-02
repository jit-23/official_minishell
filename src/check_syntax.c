/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eescalei <eescalei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 03:30:16 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/07/31 21:33:08 by eescalei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_pipe_sequence(t_token *token)
{
	while (token)
	{
		if ((token->type == PIPE && !token->next) || (token->type == PIPE
				&& !token->prev) || (token->type == PIPE && (token->next
					&& (token->next->type) == PIPE)))
		{
			ft_putstr_fd(2, "syntax error near unexpected token '|'\n");
			return (1);
		}
		token = token->next;
	}
	return (0);
}

int	check_syntax(t_shell *sh)
{
	t_token	*tmp;

	tmp = sh->token_list->official_head;
	if (check_pipe_sequence(tmp))
		return (1);
}
