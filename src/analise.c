/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analise.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 20:01:30 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/07/04 19:45:09 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
/* \n && '//' */
/* int get_pipe(t_shell *sh, t_placing placing)
{
	char *pipe_var;

	pipe_var = (char *)s_malloc(sizeof(sizeof(char) * 2));
	pipe_var[1] = '\0';
	pipe_var[0] = '|';
	add_to_list(sh->token_list, pipe_var, PIPE, placing);
	return (1);
} */
static int	get_new_line(t_shell *sh, t_placing place)
{
	char *newl;

	newl = (char *)s_malloc(sizeof(sizeof(char) * 2));
	newl[0] = '\n';
	newl[1] = '\0';
	add_to_list(sh->token_list, newl, NEW_LINE, place);
	return (1);
}

static void analise_cmdl(t_shell *shell, t_placing place, int i, char *cmdl)
{
	while(cmdl[i])
	{
		if (cmdl[i] == '\'')
			i += handle_single_quotes_type(39, shell, &place);
		else if (cmdl[i] == '\"')
			i += handle_double_quotes_type(34, shell, &place);
		else if(cmdl[i] && is_space(cmdl[i]))
			i += get_space(cmdl, i, shell, place);
		else if (cmdl[i] && cmdl[i] == '$')
			i += get_env_var(cmdl, i, shell, place);
		else if (cmdl[i] && cmdl[i] == '|')
			i += get_pipe(shell, place);
		else if (cmdl[i] && cmdl[i] == '>' || cmdl[i] == '<')
			i += get_redirect_var(cmdl, i, shell, place);
		else if (cmdl[i] && !special_char(cmdl[i]) && !is_space(cmdl[i]))
			i += get_word(cmdl, i, shell, place);
		else if (cmdl[i] && cmdl[i] == '\n')
			i += get_new_line(shell, place);
	}
//	t_token *head;
//	
//	//head = shell->refined_list->official_head;
//	
//	head = shell->token_list->official_head;
//	if (head)
//		printf("here\n");
//	else
//		printf("not here\n");
//	printf("-------------------%p\n", head);
//	while(head)
//	{
//		printf("===================\n");
//		printf("token   = .%s.\n", head->token);
//		printf("Placing = .%u.\n", head->placing);
//		printf("Type    = .%d.\n", head->type);
//		head = head->next;
//	}
}

static void refine_token_list(t_shell *sh)
{
	t_token *token;
	t_token *tmp;

	token = sh->token_list->official_head;
	while (token)
	{
		while (token->type != ENV && token->type != WORD)
			token = token->next;
		tmp = token->next;
		if (!tmp)
			break;
		if (token)
		{
			while(tmp && (tmp->type == ENV || tmp->type == WORD || tmp->type == S_QUOTE || tmp->type == D_QUOTE))
			{
				if (tmp->type == WORD || tmp->type == ENV)
					token->token = ft_strjoin(token->token, tmp->token);
				tmp = tmp->next;
			}
			if (!tmp)
				token->next = NULL;
			else
				token->next = tmp;
			token = token->next;
		}
	}
	
}
void	parse_tokens(t_shell *shell, char *cmdl)
{
	t_placing	place;

	// primeira lista feita.
	/* agr preciso de outra lista que tera os token ajustados em caso de ex: "p"d'w' == (pwd) ou  */
	//refine_token_list(shell);
}

void	analise_cmd_line(t_shell *shell, char *cmdline)
{
	//t_cmd *tmp_root;
	// trim edges on cmdline for = (' ' && '\t');
	t_placing place = DEFAULT;
	analise_cmdl(shell, place, 0, shell->cmd_line);

	//parse_tokens(shell, cmdline);
	/*if (check_syntax(shell))
		return ; */
	
	//return ;
	t_token *head;

	//head = shell->refined_list->official_head;

	head = shell->token_list->official_head;
	while(head)
	{
		printf("===================\n");
		printf("token   = .%s.\n", head->token);
		printf("Placing = .%u.\n", head->placing);
		printf("Type    = .%d.\n", head->type);
		head = head->next;
	}
	init_AST(shell);
	//tmp_root = shell->root;
	//printf("ROOT - %d\n", shell->root->type);
	print_tree(shell->root);
	//delete_all(shell);
	return ;
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
