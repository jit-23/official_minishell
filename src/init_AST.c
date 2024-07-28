/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_AST.c                                         :+:      :+:    :+:   */
/*                  x                                  +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 00:47:31 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/06/26 15:20:15 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int peek_token(t_token *checker,int var_nbr, ...)
{
    va_list ptr;
    int flag;
    int i;
    char *token;

	i = 0;
	flag = 1;
	if (!checker)
		return (0);
	token = checker->token;
	va_start(ptr, var_nbr);
	while(i < var_nbr)
	{
        flag = ft_strncmp(token , va_arg(ptr, char *), ft_strlen(token));
        if (flag == 0)
            return (1);
        i++;
    }
    va_end(ptr);
    return (0);
}

t_exec *init_exec()
{
    t_exec *exec;

    exec = (t_exec *)calloc(2, sizeof(t_exec));
    if (!exec)
    {
        ft_putstr_fd(2, "error on malloc\n");
        return (NULL);
    }
    exec->type = _EXEC;
    return (exec);
}

t_pipe *init_pipe()
{
    t_pipe *pipe;

    pipe = (t_pipe *)malloc(sizeof(t_pipe));
    if (!pipe)
    {
        ft_putstr_fd(2, "error on malloc\n");
        return (NULL);
    }
    pipe->type = _PIPE;
    pipe->left = NULL;
    pipe->right = NULL;
    return (pipe);
}

int peek_future_tokens_type(t_token *head, t_type type)
{
    t_token *tmp;

    tmp = head;
    while(tmp)
    {
        if (tmp->type == type) 
            return (1);
        tmp = tmp->next; 
    }
    return (0);
}

t_redir *init_redir()
{
	t_redir *redir;

	redir = malloc(/* 5, */ sizeof(t_redir));
	redir->type = _REDIR;
	return (redir);	
}

static int handle_token(t_shell *sh, t_exec *ex, int i)
{
	
	if (sh->refined_list->head->type == WORD)
	{
		ex->args[i] = ft_strdup(sh->refined_list->head->token);
		sh->refined_list->head = sh->refined_list->head->next;
	}
	else if (sh->refined_list->head->type == S_QUOTE)
		sh->refined_list->head = sh->refined_list->head->next;
	else if (sh->refined_list->head->type == D_QUOTE)
		sh->refined_list->head = sh->refined_list->head->next;
	else
		return 0;
	return 1;
}

t_cmd *exec_parse(t_shell*sh, t_exec *exec_struct)
{
	int		i;
	t_cmd	*branch_root;
	t_token	*prev;

	i = 0;
	prev = sh->refined_list->head->prev;
	branch_root = (t_cmd *)exec_struct;
	while (sh->refined_list->head && peek_token(sh->refined_list->head, 1, "|") == 0)
	{
		branch_root = parse_redir((t_cmd *)branch_root, sh);
		if (!sh->refined_list->head)
			break ;
		if (sh->refined_list->head && sh->refined_list->head->type == WORD || sh->refined_list->head->type == ENV)
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

void    init_AST(t_shell *sh)
{
    exec_parse(sh, init_exec());
	if (!sh->refined_list->head)
		return ;
	pipe_parse(sh, sh->root);
}

t_cmd   *pipe_parse(t_shell *sh, t_cmd *left)
{
    t_pipe *pipe_struct;

    pipe_struct = init_pipe();
    pipe_struct->left = left;
    sh->root = (t_cmd *)pipe_struct;
    if (sh->refined_list->head->next)
        sh->refined_list->head = sh->refined_list->head->next;
    if (peek_future_tokens_type(sh->refined_list->head, PIPE))
    {
        pipe_struct->right = exec_parse(sh, init_exec());
        pipe_parse(sh ,(t_cmd *)sh->root);
    }
    else if (peek_future_tokens_type(sh->refined_list->head, WORD))
        pipe_struct->right = exec_parse(sh, init_exec());
    return ((t_cmd *)pipe_struct);
}

static t_redir *fill_redir(char *s, int mode, t_shell *sh)
{
	t_redir *red;
	t_token *tmp;
	red = init_redir();
	while (sh->refined_list->head && sh->refined_list->head->type != WORD)
		sh->refined_list->head = sh->refined_list->head->next;
	red->file = sh->refined_list->head->token;
	printf("token in fill_redir - .%s.\n", sh->refined_list->head->token);
	printf("file in fill_redir - .%s.\n", red->file);
	red->mode = mode;
	return (red);
}


static	t_redir *get_last_redir(t_cmd *sub_root)
{
	t_redir *tmp;

	tmp = (t_redir *)sub_root;
	while(tmp->cmd && tmp->cmd->type ==  _REDIR)
		tmp = (t_redir *)tmp->cmd;
	return (tmp);
}
static t_redir *handle_redir_type(t_shell *sh)
{
	char *redir_type;
	int redir_type_len;
	t_redir *red;

	redir_type = sh->refined_list->head->token;
	redir_type_len = ft_strlen(redir_type);
	if (strncmp(redir_type, ">" , redir_type_len) == 0)
		red = fill_redir(">", 1, sh);
	else if (strncmp(redir_type, "<" , redir_type_len) == 0)
		red = fill_redir("<", 0, sh);
	else if (strncmp(redir_type, ">>", redir_type_len) == 0)
		red = fill_redir("<", 2, sh);
	return (red);
}

t_cmd *parse_redir(t_cmd *branch_root, t_shell *sh)
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
