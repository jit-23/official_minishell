/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:08:42 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/07/30 08:35:57 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
//#include "../includes/env.h"

//#define BLUE 			\033 [0;34m
//#define default_colour	\033 [0m

static void	get_prompt(t_shell *shell)
{
	char	*dir;

	dir = NULL;
	dir = getcwd(dir, 100);
	shell->prompt = ft_strjoin(dir, "$ ");
	shell->cmd_line = readline(shell->prompt);
	if (shell->cmd_line)
		add_history(shell->cmd_line);
	free(dir);
}

static void	print_env(t_env *e, char **ev)
{
	int	i;

	i = 0;
	while (e)
	{
		printf(ANSI_COLOR_RED "%s\n", e->env_name);
		printf(ANSI_COLOR_RESET "%s\n", ev[i]);
		e = e->next;
		i++;
	}
}

static void	print_vals(t_env *e, char **ev)
{
	int	i;

	i = 0;
	while (e)
	{
		printf(ANSI_COLOR_RED ".%s.\n", e->env_value);
		printf(ANSI_COLOR_RESET "%s\n", ev[i]);
		e = e->next;
		i++;
	}
}

static void	init_shell(t_shell *shell, char **ev)
{
	shell->ev = NULL;
	shell->env = NULL;
	shell->root = NULL;
	shell->paths = NULL;
	shell->prompt = NULL;
	shell->cmd_line = NULL;
	shell->token_list = NULL;
	shell->stop_iteration = 0;
	shell->token_list = (t_lexer *)malloc(sizeof(t_lexer));
	shell->refined_list = (t_lexer *)malloc(sizeof(t_lexer));
	shell->token_list->head = NULL;
	shell->token_list->official_head = NULL;
	shell->refined_list->head = NULL;
	shell->refined_list->official_head = NULL;
	shell->ev = expand_env(shell, ev);
}

int	main(int ac, char **av, char **ev)
{
	t_shell	shell;

	if (ac != 1)
		return (1);
	while (1)
	{
		init_shell(&shell, ev);
		get_prompt(&shell);
		if (ft_memcmp(shell.cmd_line, "exit\0", 5) == 0)
		{
			delete_all(&shell);
			return (0);
		}
		if (shell.cmd_line[0] != '\0')
			analise_terminal_input(&shell, shell.cmd_line);
		delete_all(&shell);
	}
	return (0);
}
