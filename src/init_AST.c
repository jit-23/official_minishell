/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_AST.c                                         :+:      :+:    :+:   */
/*                  x                                  +:+ +:+        
	+:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 00:47:31 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/06/26 15:20:15 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd	*pipe_parse(t_shell *sh, t_cmd *left)
{
	t_pipe	*pipe_struct;

	pipe_struct = init_pipe();
	pipe_struct->left = left;
	sh->root = (t_cmd *)pipe_struct;
	if (sh->refined_list->head->next)
		sh->refined_list->head = sh->refined_list->head->next;
	if (peek_future_tokens_type(sh->refined_list->head, PIPE))
	{
		pipe_struct->right = exec_parse(sh, init_exec());
		pipe_parse(sh, (t_cmd *)sh->root);
	}
	else if (peek_future_tokens_type(sh->refined_list->head, WORD))
		pipe_struct->right = exec_parse(sh, init_exec());
	return ((t_cmd *)pipe_struct);
}

t_cmd	*parse_redir(t_cmd *branch_root, t_shell *sh)
{
	t_redir	*ret;
	t_redir	*tmp;
	t_redir	*tmp2;

	ret = (t_redir *)branch_root;
	while (peek_token(sh->refined_list->head, 3, ">", ">>", "<"))
	{
		tmp = handle_redir_type(sh);
		if (ret->type == _EXEC)
		{
			tmp->cmd = (t_cmd *)ret;
			ret = tmp;
		}
		else if (ret->type == _REDIR)
		{
			tmp2 = get_last_redir((t_cmd *)ret);
			tmp->cmd = (t_cmd *)tmp2->cmd;
			tmp2->cmd = (t_cmd *)tmp;
		}
		sh->refined_list->head = sh->refined_list->head->next;
	}
	return ((t_cmd *)ret);
}

t_cmd	*exec_parse(t_shell *sh, t_exec *exec_struct)
{
	int		i;
	t_cmd	*branch_root;
	t_token	*prev;

	i = 0;
	prev = sh->refined_list->head->prev;
	branch_root = (t_cmd *)exec_struct;
	while (sh->refined_list->head && peek_token(sh->refined_list->head, 1,
			"|") == 0)
	{
		branch_root = parse_redir((t_cmd *)branch_root, sh);
		if (!sh->refined_list->head)
			break ;
		if (sh->refined_list->head && sh->refined_list->head->type == WORD
			|| sh->refined_list->head->type == ENV)
		{
			exec_struct->args[i++] = ft_strdup(sh->refined_list->head->token);
			sh->refined_list->head = sh->refined_list->head->next;
		}
		else
			sh->refined_list->head = sh->refined_list->head->next;
	}
	exec_struct->args[i] = NULL;
	if (prev == NULL)
		sh->root = (t_cmd *)branch_root;
	return ((t_cmd *)branch_root);
}

void	init_ast(t_shell *sh)
{
	exec_parse(sh, init_exec());
	if (!sh->refined_list->head)
		return ;
	pipe_parse(sh, sh->root);
}
