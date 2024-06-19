/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 21:09:12 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/06/14 19:22:50 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
    /* 
    * need to fill the type and args with null in the end
     */




/*  on this funct, we will create a pipe struct,
    we as norm, will have a root ptr that will point to a exec struct,
    on this funct, we will redirect that
    root ptr to our pipe struct, and redefine that older root, as our LEFT ptr,
  */






t_cmd *parse_exec(t_shell *sh, t_token **checker)
{
    t_exec *cmd_exec;
    int i;

    i = 0;
    cmd_exec = (t_exec *)malloc(sizeof(t_exec));// TODO : check for error on malloc
    cmd_exec->type = _EXEC;
    cmd_exec->args = (char **)malloc(sizeof(char) * 10);
    if (sh->token_list->head == (*checker)) // primeira iteracao do exec.
        sh->root = (t_cmd *)cmd_exec;
    while(*checker && !peek_token(*checker, 1, "|"))
    {
        if (peek_token(*checker, 2, " ", "\t"))
            *checker = (*checker)->next;
        else
        {
            cmd_exec->args[i++] = ft_strdup((*checker)->token);
            *checker = (*checker)->next;
        }
    }
    cmd_exec->args[i] = NULL;
    if ((*checker) && peek_token(*checker ,1,"|") && peek_spaces(*checker))
    {
        return ((t_cmd *)parse_pipe(sh, checker));
    }
    return ((t_cmd *)cmd_exec);
}
int peek_token(t_token *checker,int var_nbr, ...)
{
    va_list ptr;
    int flag;
    int i;
    char *token;

    i = 0;
    flag = 1;
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
int peek_spaces(t_token *checker) /* 0 if there is ONLY SPACES | 1 if there is material to work with */
{// going to use peek_token to see if there is more tokens that are not " " or tab(\t)
    t_token *tmp;

    int flag;

    flag = 0;
    tmp = checker;
    while(tmp)
    {
     //   printf("PEEK  SPACE\n");
     //   printf("TOKEN - %s\n", tmp->token);
        if (peek_token(tmp, 2, " ", "\t") == 0) //encontrou algo q n tab/space
            return (1); // there is something to keep parsing
        tmp = tmp->next;
    }
    return (0);
}

t_cmd *parse_pipe(t_shell *sh, t_token **checker)
{
    t_pipe *cmd_pipe;
    cmd_pipe = (t_pipe *)malloc(sizeof(t_pipe));
    cmd_pipe->type = _PIPE;
    cmd_pipe->left = sh->root;
    cmd_pipe->right = NULL;
    sh->root = (t_cmd *)cmd_pipe;
    if (peek_token(*checker, 1, "|"))
        (*checker) = (*checker)->next; 
    if (*checker && peek_spaces((*checker)) && peek_spaces((*checker)->next)) // check if there is more '|'// esta no token (pipe) = "|";
        cmd_pipe->right = (t_cmd *)parse_exec(sh,checker);
    
    return ((t_cmd *)cmd_pipe);
}

