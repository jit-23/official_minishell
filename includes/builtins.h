/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eescalei <eescalei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:03:31 by eescalei          #+#    #+#             */
/*   Updated: 2024/07/23 01:30:48 by eescalei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

int mini_cd(char **args, t_shell *shell);
int mini_echo(t_cmd *echo_cmd);
int	mini_env(t_shell *shell);
void	mini_exit(t_shell *shell);
int mini_pwd(void);
int	mini_env(t_shell *shell);
void	mini_exit(t_shell *shell);
int	mini_unset(char **a, t_shell *shell);

#endif