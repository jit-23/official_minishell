/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 23:00:04 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/07/15 05:49:27 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


int	is_space(int c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);	
}

int	special_char(char c)
{
    if (c == '>' || c == '<' \
    	|| c == '\n' || c == '\'' || c == '\"' || c == '$' || c == '|')
			return (1);
	return (0);
}


/* put all the fill_list functions on a file named "fill_list_utils.c" */
/*							 |
							 V 											*/
int	get_space(char *cmdl, int i, t_shell *sh, t_placing placing)
{
	char *space;

	space = ft_strdup(" ");
	add_to_list(sh->token_list, space, SPACE_BAR, placing);
	return (1);
}

int	handle_double_quotes_type(int quote_type, t_shell *sh, t_placing *placing)
{
	if (*placing == DEFAULT)
	{
		get_quote(sh, placing, quote_type);
		*placing = IN_DQ; 
	}
	else if (*placing == IN_DQ)
	{
		*placing = DEFAULT; 
		get_quote(sh, placing, quote_type);
	}
	else if (*placing == IN_SQ)
		get_quote(sh, placing, quote_type);
	return (1);
}

int	handle_single_quotes_type(int quote_type, t_shell *sh, t_placing *placing)
{
	if (*placing == DEFAULT)
	{
		get_quote(sh, placing, quote_type);
		*placing = IN_SQ; 
	}
	else if (*placing == IN_SQ)
	{
		*placing = DEFAULT;
		get_quote(sh, placing, quote_type);
	}
	else if (*placing == IN_DQ)
		get_quote(sh, placing, quote_type);
	return (1);
}

int	get_quote(t_shell *sh, t_placing *placing, char quote_type)
{
	char *quote_token;

	char *s_quote;
	char *d_quote;

	if (quote_type == '\'')
	{
		s_quote = strdup("\''");
		add_to_list(sh->token_list, s_quote, S_QUOTE, *placing);	
	}
	else if(quote_type == '\"')
	{
		d_quote = strdup("\"");
		add_to_list(sh->token_list, d_quote, D_QUOTE, *placing);	
	}
	return (1);
}


int	count_word_size(char *cmdl, int i, int count, t_placing placing)
{
	if (placing == DEFAULT)
	{
		while(cmdl[i] && !is_space(cmdl[i]) && !special_char(cmdl[i]))
		{
			count++;
			i++;
		}	
	}
	else if (placing == IN_DQ)
	{
		while(cmdl[i] && cmdl[i] != '\"')
		{
			count++;
			i++;
		}
	}
	else if (placing == IN_SQ)
	{
		while(cmdl[i] && cmdl[i] != '\'')
		{
			count++;
			i++;
		}		
	}
	return (count);
}

int	get_word(char *cmdl, int i, t_shell *sh, t_placing placing)
{
	int j;
	int count;
	char *token;

	count = 0;
	j = -1;
	count = count_word_size(cmdl, i, count, placing);
	token = ft_calloc(count, sizeof(char) * (count + 1));
	//token = malloc(/* count, */ sizeof(char) * (count + 1));
	while(++j < count)
		token[j] = cmdl[i + j];
	token[j] = '\0';
	add_to_list(sh->token_list, token, WORD, placing);
	return (count);
} 

char *get_env_str(char *cmdl, int i)
{
	int count;
	int j;
	int k;
	char *env_var;
	
	
	j = i+1;
	k = 0;
	count  = 1;
	while(cmdl[j] && !special_char(cmdl[j]) && !is_space(cmdl[j]))
	{
		count++;
		j++;
	}
	env_var = s_malloc( sizeof(char) * (count ));
	while(k < count)
		env_var[k++] = cmdl[i++];
	env_var[k] = '\0';
	return (env_var);
}

int	valid_env(char *env_var ,t_env *env_head)
{
	t_env *head;

	//printf("\t\tenv_var - %s\n", env_var);
	env_var = &env_var[1];
	head = env_head;
	while(head)
	{
		if (ft_strncmp(env_var, head->env_name, ft_strlen(env_var)) == 0) // same
			return (1);
		head = head->next;	
	}
	//printf("there is nothing to expand");
	return (0);
}

char *expand_env_var(char *env_var , t_env *head)
{
	t_env *tmp;
	char *str;
	
	str = env_var;
	tmp = head;
	env_var++;
	while(tmp)
	{
		if (ft_strncmp(env_var, tmp->env_name, ft_strlen(env_var)) == 0)
			return (ft_strdup(tmp->env_value));
		tmp = tmp->next;
	}
	//printf("LOOOL\n");
	return (str);
}

static int get_rid_off(char *alloced_mem)
{
	int len;

	len = ft_strlen(alloced_mem);
	free(alloced_mem);
	return (len);
}

int	get_env_var(char *cmdl, int i, t_shell *sh, t_placing placing)
{
	char *env_var;
	char *expanded_var;

	env_var = get_env_str(cmdl, i);// i get the literal string (ex : '$USER' || '$jdafga')
	if (valid_env(env_var, sh->ev) == 1) // 1 if exist // i check if it exist 
	{
		if (placing == IN_SQ)
		{
			expanded_var = strdup(env_var);
			add_to_list(sh->token_list, expanded_var, WORD, IN_SQ); // literal string
		}
		else
		{
			expanded_var = expand_env_var(env_var, sh->ev); // expand string
			add_to_list(sh->token_list, expanded_var, WORD, DEFAULT); // placement dont matter here?
		}
		return (get_rid_off(env_var));
	}
	if (placing == IN_SQ)
	{
		expanded_var = ft_strdup(env_var);
		add_to_list(sh->token_list, expanded_var, WORD, IN_SQ); // literal string
	}
	return (get_rid_off(env_var));
}

int get_pipe(t_shell *sh, t_placing placing)
{
	char *pipe_var;

	pipe_var = (char *)s_malloc(sizeof(sizeof(char) * 2));
	pipe_var[1] = '\0';
	pipe_var[0] = '|';
	add_to_list(sh->token_list, pipe_var, PIPE, placing);
	return (1);
}

void organize_reddir_type(t_shell *sh, char *token, t_placing placing)
{
	if (!ft_strncmp(token, ">>", ft_strlen(">>")))
		add_to_list(sh->token_list, token, DREDIREC, placing);
	else if (!ft_strncmp(token, "<<", ft_strlen("<<")))
		add_to_list(sh->token_list, token, HEREDOC, placing);
	else if (!ft_strncmp(token, "<", ft_strlen("<")))
		add_to_list(sh->token_list, token, REDIR_IN, placing);
	else if (!ft_strncmp(token, ">", ft_strlen(">")))
		add_to_list(sh->token_list, token, REDIR_OUT, placing);
	else
		perror("ERROR ON '<' OR '>' parsing");
}

/* to maintain the same character if there is more than one. otherwise we stop and go to the next. */
int get_redirect_var(char *cmdl, int i, t_shell *sh, t_placing placing)
{
	int j;
	int k;
	char var;
	char *token;

	
	j = 0;
	k = i;
	var = cmdl[i];
	while(cmdl[k++] == var)
		j++; // size of the token that maintain the same char
	k = 0;
	token = (char *)ft_calloc(j + 1,(sizeof(char ) * j + 1));
	while(k < j)
		token[k++] = cmdl[i++];	
	token[k] = '\0';
  	organize_reddir_type(sh, token, placing);
	return (ft_strlen(token));
}


/* funcao obsuleta(FO), deixei aqui por se acaso aka : F(funcao)O(obsuleta) */
t_token *jump_token(t_token *token, int action)
{
	if (action == 1) // only jump if its white spaces
	{
		while (peek_token(token, 2 , " ", "\t") == 1)
			token = token->next;
	}
	else if (action == 2) // jump token and skip possible spaces
	{
		token = token->next;
		while(peek_token(token, 2 , " ", "\t") == 1)
			token = token->next;
	}
	return (token);
}