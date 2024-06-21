/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analise.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 20:01:30 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/06/21 01:38:33 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	fill_first_list(t_shell *shell, char *cmdl)
{
	int i;
	t_placing place;
	
	i = 0;
	place = DEFAULT;
	while(cmdl[i])
	{
		if (cmdl[i] == '\'')
			i += handle_single_quotes_type(39, shell, &place);
		else if (cmdl[i] == '\"')
			i += handle_double_quotes_type(34, shell, &place);
		else if(cmdl[i] && is_space(cmdl[i]))
		{
			while(cmdl[i] == 32 || cmdl[i] == 9)
				i++;
		}
		else if (cmdl[i] && cmdl[i] == '$')
			i += get_env_var(cmdl, i, shell, place);
		else if (cmdl[i] && cmdl[i] == '|')
			i += get_pipe(shell, place);
		else if (cmdl[i] && cmdl[i] == '>' || cmdl[i] == '<')
			i += get_redirect_var(cmdl, i, shell, place);
		else if (cmdl[i] && !special_char(cmdl[i]) && !is_space(cmdl[i]))
			i += get_word(cmdl, i, shell, place);
	}
}

void	analise_cmd_line(t_shell *shell, char *cmdline)
{
	t_cmd *tmp_root;

	
	// trim edges on cmdline for = (' ' && '\t');
	fill_first_list(shell, cmdline);

	t_token *head;
	head = shell->token_list->head;
	// while(head)
	//{
	//	printf("===================\n");
	//	printf("token   = %s.\n", head->token);
	//	printf("Placing = %u.\n", head->placing);
	//	printf("Type    = %d.\n", head->type);
	//	head = head->next;
	//}
	init_AST(shell);
	//shell->stop_iteration = 0;
	//tmp_root = shell->root;
	//validate_tree(shell->root, shell);
	
	print_tree(shell->root);
	//delete_all(shell);
}	

void print_tree(t_cmd *root)
{
	static int j;
    t_exec *ex;
    t_redir *redir;
    t_pipe *pp;
    if (root == NULL)
        return ;
    if (root->type == _EXEC)
    {
        ex = (t_exec *)root;
        for (int i = 0; ex->args[i]; i++)
            printf("%d - args - %s\n",j ,ex->args[i]);
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

/* cat > file */
/*	>
	file
	cat*/
