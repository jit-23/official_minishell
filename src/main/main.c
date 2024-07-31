/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eescalei <eescalei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 21:53:08 by eescalei          #+#    #+#             */
/*   Updated: 2024/07/30 00:09:47 by eescalei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac,char **av ,char **ev)
{
	t_shell shell;

	(void)av;
	while(!(shell.stop_iteration))
	{
		init_shell(&shell, ev);
		get_prompt(&shell);
		analise_cmd_line(&shell, shell.cmd_line);
		execute_line(&shell);	//to do
		delete_all(&shell);
	}
	return 0;
}
