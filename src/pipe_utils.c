/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eescalei <eescalei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 20:52:20 by eescalei          #+#    #+#             */
/*   Updated: 2024/08/02 11:00:05 by eescalei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	set_pipe_fds(t_shell *shell, t_pipe *pip1, t_pipe *pip2, int side)
{
	int fd1[2];
	int fd2[2];

	pipe(fd1);
	if(pip2 != NULL)
	{
		pipe(fd2);
		shell->prev_pipe = fd2[0];
		if(LEFT == side)
		{
			shell->pipin = fd1[0];
			shell->pipout = fd1[1];
			shell->in = -1;
			shell->out = fd1[1];
		}
		else if(RIGHT == side)
		{
			shell->pipin = fd1[0];
			shell->pipout = fd2[1];
			shell->in = fd1[0];
			shell->out = fd2[1];
		}
	}	
	else
	{
		shell->prev_pipe = -1;
		if(LEFT == side)
		{
			reset_st_fd(shell);
			shell->pipin = fd1[0];
			shell->pipout = fd1[1];
			shell->in = dup(STDIN);
			shell->out = fd1[1];
		}
		else if(RIGHT == side)
		{
			shell->pipin = fd1[0];
			shell->pipout = fd1[1];
			shell->in = fd1[0];
			shell->out = dup(STDOUT);
		}
	}
}