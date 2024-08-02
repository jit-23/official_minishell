/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eescalei <eescalei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 02:26:23 by eescalei          #+#    #+#             */
/*   Updated: 2024/07/31 21:42:37 by eescalei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	print_error(int error, const char *arg)
{
	int		i;

	if (error == -1)
		ft_putstr_fd("export: not valid in this context: ", STDERR);
	else if (error == 0 || error == -3)
		ft_putstr_fd("export: not a valid identifier: ", STDERR);
	i = 0;
	while (arg[i] && (arg[i] != '=' || error == -3))
	{
		write(STDERR, &arg[i], 1);
		i++;
	}
	write(STDERR, "\n", 1);
	return (ERROR);
}

int env_add(t_env *ev, const char *arg)
{
	t_env	*new;
	t_env	*tmp;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (ERROR);
	new->env_name = ft_strdup(arg); // change to func that cut string when position == '='
	new->env_value = ft_strdup("");	// change to func that cut string when position == '='
	new->next = NULL;
	if (!ev)
		return (new);
	tmp = ev;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (SUCCESS);
}

char		*get_env_name(char *dest, const char *src)
{
	int		i;

	i = 0;
	while (src[i] && src[i] != '=' && ft_strlen(src) < BUFF_SIZE)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	is_in_env(t_env *ev, const char *arg)
{
	char *var_name[BUFF_SIZE];
	char *env_name;
	t_env *tmp;

	tmp = ev;
	get_env_name(var_name, arg);
	while(tmp)
	{
		env_name = ev->env_name;
		if(ft_strcmp(env_name, var_name) == 0)
		{
			free(ev->env_name);
			ev->env_name = ft_strdup(var_name); // change to func that cut string when position == '='
			free(ev->env_value);
			ev->env_value = ft_strdup(arg);// change to func that cut string when position == '='
			return (ERROR);
		}
		ev = ev->next;
	}
	return (SUCCESS);
}
int	mini_export(char **args, t_env *ev, t_env *hiden) // ^ problemas com estrutura ^
{
	int	new_ev;
	int	status;

	new_ev = 0;
	if(!args[1])
	{
		print_env(hiden); // TO DO
		return (SUCCESS);
	}
	else
	{
		status = check_env(args[1]);
		if (args[1][0] == '=' )
			status = -3;
		if(status <= 0)
			return (print_error(status, args[1]));
		new_ev = status == 2 ? 1 : is_in_env(ev, args[1]);
		if(new_ev == 0)
		{
			if(status == 1)
				add_env(args[1], ev);
			add_env(args[1], hiden);
		}
	}
	return (SUCCESS);
}