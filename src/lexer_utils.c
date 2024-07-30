/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 07:30:46 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/07/30 08:05:46 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_space(int c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int	special_char(char c)
{
	if (c == '>' || c == '<' || c == '\n' || c == '\'' || c == '\"'
		|| c == '$' || c == '|')
		return (1);
	return (0);
}

int	count_word_size(char *cmdl, int i, int count, t_placing placing)
{
	if (placing == DEFAULT)
	{
		while (cmdl[i] && !is_space(cmdl[i]) && !special_char(cmdl[i]))
		{
			count++;
			i++;
		}
	}
	else if (placing == IN_DQ)
	{
		while (cmdl[i] && cmdl[i] != '\"')
		{
			count++;
			i++;
		}
	}
	else if (placing == IN_SQ)
	{
		while (cmdl[i] && cmdl[i] != '\'')
		{
			count++;
			i++;
		}
	}
	return (count);
}
