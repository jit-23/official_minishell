/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analise.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 20:01:30 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/07/30 04:37:04 by fde-jesu         ###   ########.fr       */
/*									                                          */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* void	print_tree(t_cmd *root)
{
	static int	j;
	t_exec		*ex;
	t_redir		*redir;
	t_pipe		*pp;

	if (root == NULL)
		return ;
	if (root->type == _EXEC)
	{
		ex = (t_exec *)root;
		for (int i = 0; ex->args[i]; i++)
			printf("%d - args - %s\n", j, ex->args[i]);
		j++;
		printf("\n");
	}
	else if (root->type == _REDIR)
	{
		redir = (t_redir *)root;
		print_tree((t_cmd *)redir->cmd);
		printf("redir mode(%d)\nfile %s\n", redir->mode, redir->file);
	}
	else if (root->type == _PIPE)
	{
		pp = (t_pipe *)root;
		printf("%d pipe - | \n", j);
		j++;
		print_tree((t_cmd *)pp->left);
		print_tree((t_cmd *)pp->right);
	}
}
 */

void	parse_tokens(t_shell *shell, char *cmdl)
{
	t_placing	place;

	place = DEFAULT;
	analise_cmdl(shell, place, 0, shell->cmd_line);
	refine_token_list(shell);
}

void	analise_terminal_input(t_shell *shell, char *cmdline)
{
	t_placing	place;
	t_token		*head;

	shell->cmd_line = ft_strtrim(shell->cmd_line, " \t");
	if (cmdline[0])
		return ;
	place = DEFAULT;
	parse_tokens(shell, cmdline);
	if (check_syntax(shell))
	{
		printf("syntax error\n");
		return ;
	}
	head = shell->refined_list->official_head;
	while (head)
	{
		printf("===================\n");
		printf("address = .%p.\n", head);
		printf("token   = .%s.\n", head->token);
		printf("Placing = .%u.\n", head->placing);
		printf("Type    = .%d.\n", head->type);
		head = head->next;
	}
	init_ast(shell);
	return ;
}

int	get_new_line(t_shell *sh, t_placing place)
{
	char	*newl;

	newl = ft_strdup("\n");
	add_to_list(sh->token_list, newl, NEW_LINE, place);
	return (1);
}
