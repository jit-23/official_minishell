/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:08:42 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/06/19 13:00:28 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/env.h"


//#define BLUE 			\033 [0;34m
//#define default_colour	\033 [0m


static void get_prompt(t_shell *shell)
{
    char *dir;

    dir = NULL;
    dir = getcwd(dir, 100);
    shell->prompt = ft_strjoin(dir, "$ ");
    shell->cmd_line = readline(shell->prompt);
    if (shell->cmd_line)
        add_history(shell->cmd_line);
    free(dir);
}

static void print_env(t_env *e, char **ev)
{
	int i = 0;
	while(e)
	{
		printf(ANSI_COLOR_RED "%s\n", e->env_name);
		printf( ANSI_COLOR_RESET"%s\n", ev[i]);
		e = e->next;
		i++;
	}	
}

static void print_vals(t_env *e, char **ev)
{
	int i = 0;
	while(e)
	{
	printf(ANSI_COLOR_RED ".%s.\n", e->env_value);
	printf( ANSI_COLOR_RESET"%s\n", ev[i]);
		e = e->next;
		i++;
	}	
}

int main(int ac,char **av ,char **ev)
{
	t_shell shell;
	if (ac != 1)
    	return (1); // msg erro
	shell.ev = expand_env(&shell,ev); //list of env var, separated the val and the designated name.
	shell.paths = get_path(&shell);
	while(1)
    {
    	get_prompt(&shell);
		if (strncmp(shell.cmd_line, "exit", 4) == 0)
		{
			delete_env_lst(shell.ev, lst_size_env(shell.ev));
			free(shell.prompt);
			free(shell.cmd_line);
			return 0;
		}
		if (shell.cmd_line)
		    analise_cmd_line(&shell, shell.cmd_line);
		free(shell.prompt);
		free(shell.cmd_line);
	}
    return 0;
}

/* util to read 2d arrays */

void print_loop(char **s)
{
	int i;

	i = -1;
	while(s[++i])
		printf("|.%s.|\n", s[i]);
}