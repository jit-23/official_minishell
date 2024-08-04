/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eescalei <eescalei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 20:52:20 by eescalei          #+#    #+#             */
/*   Updated: 2024/08/04 05:51:14 by eescalei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	set_pipe_fds(t_shell *shell, t_cmd *cmd)
{
	if(shell->current_pipe == NULL) // initialize values in main and after loops // cehck dup2 files order 
		return ;					//problems when next pipe depends on output feom prev
	if(shell->prev_pipe == NULL && shell->current_pipe != NULL)
	{
		if(shell->current_pipe->right == cmd)
		{
			close(shell->current_pipe->fd[1]);
			dup2(shell->current_pipe->fd[0], STDIN);
			return ;
		}
		close(shell->current_pipe->fd[0]);
		dup2(shell->current_pipe->fd[1], STDOUT);
		return ;
	}
	if(shell->current_pipe->right == cmd)
	{
		close(shell->current_pipe->fd[1]);
		close(shell->prev_pipe->fd[0]);
		dup2(shell->current_pipe->fd[0], STDIN);
		dup2(shell->prev_pipe->fd[1], STDOUT);
		return ;
	}
	close(shell->current_pipe->fd[1]);
	close(shell->prev_pipe->fd[0]);
	close(shell->prev_pipe->fd[1]);
	dup2(shell->current_pipe->fd[1], STDOUT);
	
}











// 	{

// 		pipe(fd2);
// 		shell->prev_pipe = fd2[0];
// 		if(LEFT == side)
// 		{
// 			shell->in = STDIN;
// 			shell->out = fd1[1];
// 			close(fd2[0]);
// 			close(fd2[1]);
// 			close(fd1[0]);
// 			dup2(STDOUT, shell->out);
// 		}
// 		else if(RIGHT == side)
// 		{
// 			shell->in = fd1[0];
// 			shell->out = fd2[1];
// 			close(fd1[1]);
// 			close(fd2[0]);
// 			dup2(shell->in, STDIN);
// 			dup2(STDOUT, shell->out);
// 		}
// 	}	
// 	else
// 	{
// 		shell->prev_pipe = -1;
// 		if(LEFT == side)
// 		{
// 			reset_st_fd(shell);
// 			shell->in = STDIN;
// 			shell->out = fd1[1];
// 			close(fd1[0]);
// 			dup2(STDOUT ,shell->out);//cange dup2 files order
// 		}
// 		else if(RIGHT == side)
// 		{
// 			shell->in = fd1[0];
// 			shell->out = STDOUT;
// 			close(fd1[1]);
// 			dup2(STDIN, shell->in);
// 		}
// 	}
// }