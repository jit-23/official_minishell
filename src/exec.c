/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eescalei <eescalei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 21:58:30 by eescalei          #+#    #+#             */
/*   Updated: 2024/08/02 11:05:47 by eescalei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void get_cmd_path(char **path, char **envp)
{
	int	i;

	i = 0;
	while(envp[i] != NULL)
	{
		if(ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			ft_splitt(&(path), envp[i] + 5, ':');
			break ;
		}
		i++;
	}
	if(path == NULL)
	{
		// print_error(pipex, "Error getting path\n");
		return;
	}
}

char * get_cmds(char **path, char *cmd)
{
	int i;
	char *sub_path;
	char *cmd_path;

	i = 0;
	cmd_path = NULL;
	while (path[i] != NULL)
	{
		sub_path = ft_strjoin(path[i], "/");
		cmd_path = ft_strjoin(sub_path, cmd);
		if(access(cmd_path, X_OK) == 0)
		{
			cmd_path = cmd_path;
			free(path);
			return (cmd_path);
		}
		free(sub_path);
		free(cmd_path);
		i++;
	}	
}
 
void execute_cmd(t_shell *shell, t_exec *cmd)
{
	char **path;
	char *exec_path;
//create new process
	get_cmd_path(path, shell->env);
	// handle_pipes(shell, (t_cmd *)cmd);maybe not necessary
	get_cmds(path, cmd->args[0]);
	if(!path)
		// print_error(pipex, "Error: command not found\n");
	execve(exec_path, cmd->args, shell->env); // set $? to exit code
	//check if args is null terminated
}

void redir_exec(t_shell *shell, t_cmd *cmd)
{
	if(cmd->type == _EXEC)
		execute_cmd(shell, (t_exec *)cmd);
	// else if(cmd->type == _REDIR)
	// 	execute_redir(shell, (t_redir *)cmd);	
}

void execute_line(t_shell *shell)
{
	t_cmd *cmd;
	int status;

	cmd = next_run(shell); // iniciate pipe->fd[2] = -1
	while(shell->root != NULL)
	{
		// shell->charge = 1;
		// shell->parent = 1;
		// shell->last = 1;
		//finish  values setup
		redir_exec(shell, cmd);//TO DO
		waitpid(-1, &status, 0);
		status = WEXITSTATUS(status);
		shell->ret = (shell->last == 0) ? status : shell->ret;
		if(shell->parent == 0)
		{
			//free_token(shell);// free token
			exit(shell->ret);
		}
		shell->no_exec = 0;
		// free() free cmd usado e pipe caso right  cmd
		next_run(shell);
	}
}
