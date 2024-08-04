/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eescalei <eescalei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 22:05:53 by eescalei          #+#    #+#             */
/*   Updated: 2024/08/04 04:29:38 by eescalei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void close_fd(int fd)
{
	if (fd < 0)
		close(fd);
}

void reset_st_fd(t_shell *shell)
{
	dup2(shell->fdin, STDIN);
	dup2(shell->fdout, STDOUT);
}

void close_fds(t_shell *shell)
{
	close_fd(shell->fdin);
	close_fd(shell->fdout);
}

void reset_fd(t_shell *shell)
{
	shell->fdin = -1;
	shell->fdout = -1;
	shell->pid = -1;
}

void	open_pipes(t_shell *shell)
{
	if(shell->current_pipe != NULL && shell->current_pipe->fd[0] == -1)
		pipe(shell->current_pipe->fd);
	if(shell->prev_pipe != NULL && shell->prev_pipe->fd[0] == -1)
		pipe(shell->prev_pipe->fd);
}