/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eescalei <eescalei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 21:58:30 by eescalei          #+#    #+#             */
/*   Updated: 2024/07/30 04:51:00 by eescalei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char * get_cmds(char **path, char *cmd)
{
	int i;
	char *path;
	char *cmd_path;

	i = 0;
	cmd_path = NULL;
	while (path[i] != NULL)
	{
		path = ft_strjoin(path[i], "/");
		cmd_path = ft_strjoin(path, cmd[0]);
		if(access(cmd_path, X_OK) == 0)
		{
			cmd_path = cmd_path;
			free(path);
			return (cmd_path);
		}
		free(path);
		free(cmd_path);
		i++;
	}	
}

void redir_exec(t_shell *shell, t_token *token)
{
	if(token->type == _EXEC)
		execte_cmd(shell, token);
	else if(token->type == _PIPE)
		execute_pipe(shell, token);
	else if(token->type == _REDIR)
		execute_redir(shell, token); // wait instruction from parse		
}

void execute_line(t_shell *shell)
{
	t_token *token;
	int status;

	// token = next_run(shell->) // iniciar token
	while(!(shell->stop_iteration))
	{
		shell->charge = 1;
		shell->parent = 1;
		shell->last = 1;
		//finish  values setup
		redir_exec(shell, token);//TO DO
		waitpid(-1, &status, 0);
		status = WEXITSTATUS(status);
		shell->ret = (shell->last == 0) ? status : shell->ret;
		if(shell->parent == 0)
		{
			//free_token(shell);// free token
			exit(shell->ret);
		}
		shell->no_exec = 0;
		//next run
	}
}
