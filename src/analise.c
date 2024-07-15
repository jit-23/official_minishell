/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analise.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 20:01:30 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/07/15 06:17:40 by fde-jesu         ###   ########.fr       */
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

/* static void refine_token_list(t_shell *sh)
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
} */

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
	//printf("last->next->token - %s\n",last->next->token);
	prev = last;
	last = last->next;
	last->prev = prev;
}

//static void handle_word_token(t_shell *sh)
//{
//	char *w;
//	char *a;
//	t_token *og;
//	char *p;
//
//
//	og = sh->token_list->head;
//	a = NULL;
//	w = malloc(sizeof(char) * 1);
//	w[0] = '\0';
//	while(sh->token_list->head && (sh->token_list->head->type == ENV || sh->token_list->head->type == WORD || sh->token_list->head->type == S_QUOTE || sh->token_list->head->type == D_QUOTE))
//	{
//		if(sh->token_list->head && (sh->token_list->head->type == WORD || sh->token_list->head->type == ENV))
//		{
//			if (sh->token_list->head && (sh->token_list->head->type == ENV || sh->token_list->head->type == WORD || sh->token_list->head->type == S_QUOTE || sh->token_list->head->type == D_QUOTE))
//			{
//				if (sh->token_list->head->type == ENV || sh->token_list->head->type == WORD)
//				{
//					w = ft_strjoin(w, sh->token_list->head->token);
//				}
//				else
//				{
//					sh->token_list->head = sh->token_list->head->next;
//				}
//				/* printf("\tw - .%s.\n", w);
//				printf("\tsh->token_list->head->token - .%s.\n",sh->token_list->head->token);
//				w = ft_strjoin(w, sh->token_list->head->token);
//				printf("\ttoken colado - %s\n", w);
//				printf("token --- %s\n", w); */
//			}
//		}	
//			sh->token_list->head = sh->token_list->head->next;
//	}
//	add_to_refined_list(sh->refined_list, w, og->type);
//}

 static void handle_word_token(t_shell *sh)
{
	char *w;
	char *a;
	t_token *og;
	char *p;


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
			else
				sh->token_list->head = sh->token_list->head->next;
			sh->token_list->head = sh->token_list->head->next;
	}
	add_to_refined_list(sh->refined_list, w, og->type);
}

static void refine_token_list(t_shell *sh)
{
	t_token  *token;

	//sh->token_list->head;
	while(sh->token_list->head)
	{
		printf("loop0\n");
		if (sh->token_list->head->type == WORD)
		{
			printf("loop1\n");
			handle_word_token(sh);
			printf("loop2\n");
		}
		else if (sh->token_list->head->type == ENV)
			handle_word_token(sh);
		printf("hereee\n");
		printf("token - %p\n", sh->token_list->head);
		//else if (sh->token_list->head->type == DREDIREC)
		if (!sh->token_list->head)
			break ;
		sh->token_list->head = sh->token_list->head->next;
		printf("hereee\n");

	}	
}

void	parse_tokens(t_shell *shell, char *cmdl)
{
	t_placing	place;

	place = DEFAULT;
	analise_cmdl(shell, place, 0, shell->cmd_line);
	refine_token_list(shell/* , shell->token_list->official_head */);
	// primeira lista feita.
	/* t_token *head;
	head = shell->token_list->official_head;
	while(head)
	{
		printf("..............\n");
		printf("address = .%p.\n", head);
		printf("address = .%s.\n", head->token);
		printf("..............\n");
		head = head->next;
	} */
	/* agr preciso de outra lista que tera os token ajustados em caso de ex: "p"d'w' == (pwd) ou  */
}

void	analise_cmd_line(t_shell *shell, char *cmdline)
{
	//t_cmd *tmp_root;
	// trim edges on cmdline for = (' ' && '\t');
	t_placing place = DEFAULT;
	parse_tokens(shell, cmdline);
//	if (check_syntax(shell))
//	{
//		printf("lol\n");
//		return ;
//	}

	t_token *head;
	//head = shell->refined_list->official_head;

	head = shell->refined_list->official_head;
	printf("here\n");
	while(head)
	{
		printf("===================\n");
		printf("address = .%p.\n", head);
		printf("token   = .%s.\n", head->token);
		printf("Placing = .%u.\n", head->placing);
		printf("Type    = .%d.\n", head->type);
		head = head->next;
	}
	printf("\t\tdddddd\n");
	return ;
	init_AST(shell);
	print_tree(shell->root);
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
