/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:07:57 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/07/27 23:41:18 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* clear linked list for the env vars. */
#include "../includes/minishell.h"

void delete_all(t_shell *shell)
{
	if (shell->cmd_line)
		free(shell->cmd_line);
	if (shell->prompt)
		free(shell->prompt);
	if (shell->token_list) // tenho q initializar->->->-> // aqui tenho problema de reaidn g->->->->
		delete_token_lst(shell->token_list->official_head, lst_size_tokens(shell->token_list->official_head));
	if (shell->refined_list)
		delete_token_lst(shell->refined_list->official_head, lst_size_tokens(shell->refined_list->official_head));
	if (shell->root)
		delete_tree(shell->root);
	if (shell->token_list)
		free(shell->token_list);
	if (shell->refined_list)
		free(shell->refined_list);
	if (shell->ev)
		delete_env_lst(shell->ev, lst_size_env(shell->ev));
}


void clean_for_next_loop(t_shell *sh)
{
	if (sh->cmd_line)
		free(sh->cmd_line);
	if (sh->prompt)
		free(sh->prompt);
	if (sh->token_list->head)
		delete_token_lst(sh->token_list->head, lst_size_tokens(sh->token_list->head));
	if (sh->root)
		delete_tree(sh->root);
}

/* delete tokens that contain the env vars and its value */

static  void delete_exec(t_exec *ex)
{
	int i;

	i = -1;
	while(ex->args[++i])
		free(ex->args[i]);
	free(ex);
}

static void delete_pipe(t_pipe *pp)
{
	free(pp);
}

static void delete_redir(t_redir *redir)
{
	free(redir);
}

void delete_tree(t_cmd *root)
{
    t_exec *ex;
    t_redir *redir;
    t_pipe *pp;

    if (root == NULL)
        return ;
    if (root->type == _EXEC)
		delete_exec((t_exec *)root);
	else if (root->type == _REDIR)
	{
		redir = (t_redir *)root;
		delete_tree((t_cmd *)redir->cmd);
		delete_redir(redir);
	}
    else if (root->type == _PIPE)
    {
        pp = (t_pipe *)root;
        delete_tree((t_cmd *)pp->left);
        delete_tree((t_cmd *)pp->right);
		delete_pipe(pp);
    }
}
