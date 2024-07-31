/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eescalei <eescalei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 04:19:33 by eescalei          #+#    #+#             */
/*   Updated: 2024/07/30 04:22:58 by eescalei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLS_H
# define TOOLS_H

# include "minishell.h"

/* 
**	STRINGS
 */
int ft_splitt(char ***strs, char *s, char c);
int ft_substrr(char ***str, char *s, int start, int len, int j);

/* 
**	FDS
 */
void close_fd(int fd);
void reset_st_fd(t_shell *shell);
void close_fd(t_shell *shell);
void reset_fd(t_shell *shell);

/* 
**	TOKENS
 */
t_token	*next_run(t_token *token, int skip);


#endif