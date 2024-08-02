/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 06:13:01 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/07/30 07:47:19 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	delete_exec(t_exec *ex)
{
	int	i;

	i = -1;
	while (ex->args[++i])
		free(ex->args[i]);
	free(ex);
}

static void	delete_pipe(t_pipe *pp)
{
	free(pp);
}

static void	delete_redir(t_redir *redir)
{
	free(redir);
}

void	delete_tree(t_cmd *root)
{
	t_exec	*ex;
	t_redir *redir;
	t_pipe	*pp;

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
