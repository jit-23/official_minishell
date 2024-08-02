/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eescalei <eescalei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 21:58:30 by eescalei          #+#    #+#             */
/*   Updated: 2024/08/02 15:32:12 by eescalei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"



char * get_cmds(char **path, char *cmd)
{
	int i;
	char *sub_path;
	char *cmd_path;

	i = 0;
	cmd_path = NULL;
	sub_path = NULL;
	printf("%s\n", path[1]);
	while (path[i] != NULL)
	{
		printf("%s\n", cmd);
		sub_path = ft_strjoin(path[i], "/");
		cmd_path = ft_strjoin(sub_path, cmd);
		if(access(cmd_path, X_OK) == 0)
		{
			free(sub_path);
			return (cmd_path);
		}
		free(sub_path);
		free(cmd_path);
		i++;
	}	
}
 
void execute_cmd(t_shell *shell, t_exec *cmd)
{
	char *exec_path;

	exec_path = get_cmds(shell->path, cmd->args[0]);
	// if(!shell->path)
	// 	printf("env path not found");// print_error(pipex, "Error: command not found\n");
	shell->pid = fork();
	if(shell->pid == 0)
		execve(exec_path, cmd->args, shell->env); // set $? to exit code
	// //check if args is null terminated
	// if(shell->pid != 0)
	// 	printf(" child ok");
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

	cmd = shell->root;
	// print_tree(shell->root);
	// printf("%i", cmd->type); // iniciate pipe->fd[2] = -1
	/* cmd = next_run(shell); */
	if(cmd != NULL)
	{
		// shell->charge = 1;
		// shell->parent = 1;
		// shell->last = 1;
		//finish  values setup
		redir_exec(shell, cmd);//TO DO
		// waitpid(-1, &status, 0);
		// status = WEXITSTATUS(status);
		// shell->ret = (shell->last == 0) ? status : shell->ret;
		// if(shell->parent == 0)
		// {
		// 	//free_token(shell);// free token
		// 	exit(shell->ret);
		// }
		// shell->no_exec = 0;
		// // free() free cmd usado e pipe caso right  cmd
		// next_run(shell);
	}
}
