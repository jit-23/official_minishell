/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analise.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 20:01:30 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/07/27 23:57:02 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	get_new_line(t_shell *sh, t_placing place)
{
	char *newl;

	newl = ft_strdup("\n");
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
}

static void add_to_refined_list(t_lexer *token_refined, char *word, t_type type)
{
	t_token *head;
	t_token *prev;
	t_token *last;
	if (!token_refined->head)
	{
		
		token_refined->head = new_node(word, type, 0);
		token_refined->head->prev = NULL;
		token_refined->official_head = token_refined->head;
		return ;
	}
	last = ft_lstlast(token_refined->head);
	last->next = new_node(word, type, 0);
	prev = last;
	last = last->next;
	last->prev = prev;
}



static void handle_word_token(t_shell *sh)
{
	char	*w;
	char	*a;
	t_token	*og;

	og = sh->token_list->head;
	a = NULL;
	w = ft_strdup("");
	while(sh->token_list->head && (sh->token_list->head->type == ENV || sh->token_list->head->type == WORD || sh->token_list->head->type == S_QUOTE || sh->token_list->head->type == D_QUOTE))
	{
		if (sh->token_list->head->type == ENV || sh->token_list->head->type == WORD)
		{
			a = ft_strjoin(w, sh->token_list->head->token);
			free(w);
			w = a;
		}
		sh->token_list->head = sh->token_list->head->next;
		if (sh->token_list->head && sh->token_list->head->type == SPACE_BAR)
		{ 
		//	printf("(refined)token - .%s.\n", sh->token_list->head->token);
			//sh->token_list->head = sh->token_list->head->next;
		}			
	}
	//if (sh->token_list->head)
	//	printf("(refined outside) token - .%s.\n", sh->token_list->head->token);
	add_to_refined_list(sh->refined_list, w, og->type);
}

static void handle_token(t_shell *sh, char *token)
{
	char *pipe;

	pipe = ft_strdup(token);
	add_to_refined_list(sh->refined_list, pipe, sh->token_list->head->type);
	sh->token_list->head = sh->token_list->head->next;
}

static void refine_token_list(t_shell *sh)
{
	while(sh->token_list->head)
	{
		if (sh->token_list->head->type == WORD)
			handle_word_token(sh);
		else if (sh->token_list->head->type == SPACE_BAR)
			handle_token(sh, " ");
		else if (sh->token_list->head->type == ENV)
			handle_word_token(sh);
		else if (sh->token_list->head->type == S_QUOTE || sh->token_list->head->type == D_QUOTE)
			sh->token_list->head = sh->token_list->head->next;
		else if (sh->token_list->head->type == PIPE)
			handle_token(sh, "|");
		else if (sh->token_list->head->type == REDIR_IN)
			handle_token(sh, "<");
		else if (sh->token_list->head->type == 	REDIR_OUT)
			handle_token(sh, ">");
		else if (sh->token_list->head->type == HEREDOC)
			handle_token(sh, "<<");
		if (!sh->token_list->head)
			break ;
	}	
}

void	parse_tokens(t_shell *shell, char *cmdl)
{
	t_placing	place;

	place = DEFAULT;
	analise_cmdl(shell, place, 0, shell->cmd_line);
	refine_token_list(shell);
}

void	analise_cmd_line(t_shell *shell, char *cmdline)
{
	shell->cmd_line = ft_strtrim(shell->cmd_line, " ");
	printf("\t\t\t\t\tshell->cmd_line - .%s.\n", shell->cmd_line);
	// trim edges on cmdline for = (' ' && '\t');
	t_placing place = DEFAULT;
	parse_tokens(shell, cmdline);
	if (check_syntax(shell))
	{
		printf("syntax error\n");
		return ;
	}

	t_token *head;
	//head = shell->refined_list->official_head;

	head = shell->refined_list->official_head;
	while(head)
	{
		printf("===================\n");
		printf("address = .%p.\n", head);
		printf("token   = .%s.\n", head->token);
		printf("Placing = .%u.\n", head->placing);
		printf("Type    = .%d.\n", head->type);
		head = head->next;
	}
	init_AST(shell);
	print_tree(shell->root);
	printf(".1.\n");
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
