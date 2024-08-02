/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eescalei <eescalei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 20:56:34 by eescalei          #+#    #+#             */
/*   Updated: 2024/07/31 21:42:00 by eescalei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_error(char **args)
{
	ft_putstr_fd("cd: ", 1);
	if(args[2])
		ft_putstr_fd("string not in pwd: ", 1);
	else
	{
		ft_putstr_fd(strerror(errno), 1);
		ft_putstr_fd(": ", 1);
	}
	ft_putstr_fd(args[1], 1);
}	

int	update_old_pwd(char **env)
{
	char *cwd[PATH_MAX];
	char *old_pwd;

	if(getcwd(cwd, PATH_MAX) == NULL)
		return (ERROR);
	if(!(old_pwd = strjoin("OLDPWD=", cwd)))
		return (ERROR);
	if(is_in_env(env, old_pwd)) //TO DO
		env_add(env, old_pwd);  //TO DO
	free(old_pwd);
	return (SUCCESS);
}

int	go_to_path(int option, char **env)
{
	int status;
	char *env_path;

	env_path = NULL;
	if(option == 0)
	{
		update_old_pwd(env);
		// env_path = get_env("HOME", env, 4); // to do
		if(env_path)
			write(2, "cd: HOME not set\n", 17);
		if(env_path)
			return (1);
	}
	else if(option == 1)
	{
		// env_path = get_env("OLDPWD", env, 4);
		if(env_path)
			write(2, "cd: OLDPWD not set\n", 17);
		if(env_path)
			return (1);
		update_old_pwd(env);
	}
	status = chdir(env_path);
	free(env_path);
	return (status);
}

int mini_cd(char **args, t_shell *shell)
{
	char **env;
	int status;

	status = -1;
	env = shell->env;
	if(!args[1])
		return (go_to_path(0, env)); 	//TO DO
	if(ft_strncmp(args[1], "~", 1) == 0)
		return (go_to_path(1, env));
	else
	{
		update_old_pwd(env);
		status = chdir(args[1]);
		if(status != 0)
			print_error(args);
	}
	return (status);
}
