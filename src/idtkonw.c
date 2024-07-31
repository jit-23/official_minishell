/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eescalei <eescalei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:08:42 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/07/29 21:52:40 by eescalei         ###   ########.fr       */
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

void print_loop(char **s)
{
	int i;

	i = -1;
	while(s[++i])
		printf("|.%s.|\n", s[i]);
}