/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eescalei <eescalei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 21:58:30 by eescalei          #+#    #+#             */
/*   Updated: 2024/08/04 05:34:54 by eescalei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_cmd_run(t_shell *shell, t_cmd *cmd) // check if all :after free cmd put it = NULL
{
	if(cmd == shell->root)						// with valgring loop in exec dont break
	{
		free(cmd);
		shell->root = NULL;
	}
	else if(shell->current_pipe->right == cmd)
	{
		if((t_cmd *)shell->current_pipe == shell->root)
			shell->root = NULL;
		free(cmd);
		free(shell->current_pipe);
		shell->current_pipe = NULL;
		if(shell->prev_pipe != NULL)
			shell->prev_pipe->left = NULL;
		shell->prev_pipe = NULL;
		return ;
	}
	else
	{
		free(cmd);
		shell->current_pipe->left = NULL;
		shell->prev_pipe = NULL;
		shell->current_pipe = NULL;
	}	
}

char * get_cmds(char **path, char *cmd)
{
	int i;
	char *sub_path;
	char *cmd_path;

	i = 0;
	cmd_path = NULL;
	sub_path = NULL;
	while (path[i] != NULL)
	{
		printf("%s\n", cmd);
		sub_path = ft_strjoin(path[i], "/");
		cmd_path = ft_strjoin(sub_path, cmd);
		if(access(cmd_path, X_OK) == 0)
		{
			printf("path : %s\n", cmd_path);
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
	if(shell->pid == 0) // close unecesary fds PS: probably theres a func better suited somewhere
	{
		set_pipe_fds(shell,(t_cmd *)cmd);
		printf("cmd ready to execute\n\n");
		execve(exec_path, cmd->args, shell->env); // set $? to exit code
	}	
	waitpid(shell->pid, &shell->last_status, 0); // wait in func where execute
	printf("cmd executed\n\n");	
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

	status = -1;
	cmd = shell->root;
	// print_tree(shell->root);
	// printf("%i", cmd->type); // iniciate pipe->fd[2] = -1
	while(shell->root != NULL)
	{
		cmd = next_run(shell);
		printf("\nnext run: %s\n type: %i\n", ((t_exec *)cmd)->args[0], cmd->type);
		//finish  values setup
		open_pipes(shell);
	//	manage_pipes PS: do it in chld process
		redir_exec(shell, cmd);//TO DO
		// status = WEXITSTATUS(status);
		// shell->ret = (shell->last == 0) ? status : shell->ret;
		// if(shell->parent == 0)
		// {
		// 	//free_token(shell);// free token
		// 	exit(shell->ret);
		// }
		// shell->no_exec = 0;
		free_cmd_run(shell, cmd); //free cmd usado e pipe caso right  cmd
	}
}
