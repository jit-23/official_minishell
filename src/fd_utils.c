/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eescalei <eescalei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 22:05:53 by eescalei          #+#    #+#             */
/*   Updated: 2024/08/02 10:40:34 by eescalei         ###   ########.fr       */
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
	close_fd(shell->pipin);
	close_fd(shell->pipout);
}

void reset_fd(t_shell *shell)
{
	shell->fdin = -1;
	shell->fdout = -1;
	shell->pipin = -1;
	shell->pipout = -1;
	shell->pid = -1;
}
