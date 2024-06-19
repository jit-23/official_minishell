/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 04:36:48 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/06/19 13:16:49 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int is_path_env(char *s)
{
	if (ft_strncmp(s, "PATH", ft_strlen(s)) == 0)
		return (1);
	return (0);
}

char **get_path(t_shell *sh)
{
	t_env *tmp;
	char **paths;
	tmp = sh->ev;
	while(!is_path_env(tmp->env_name))
		tmp = tmp->next;
	//printf("tmp->env_value - %s\n",tmp->env_value);
	paths = ft_split(tmp->env_value, ':');
	return (paths);
}

char **get_absolute_executable(t_exec *executable, t_shell *sh)
{
	int		i;
	char	**absolute_executables; // paths with the designed cmd
	char	*cmd;
	t_env	*tmp;
	tmp = sh->ev;
	i = 0;
	while(!is_path_env(tmp->env_name))
		tmp = tmp->next;
	cmd = ft_strjoin("/", executable->args[0]); //  -  "/ls"
	absolute_executables = s_malloc(ft_count(tmp->env_value, ':') + 1);
	while(sh->paths[i])
	{
		absolute_executables[i] = ft_strjoin(sh->paths[i], cmd);
		i++;
	}
	absolute_executables[i] = NULL;
	return (absolute_executables);
}

/*  this executables are random, i just strjoin the cmd to the end off each path.
so now im trying to find it */
void validate_exec(t_exec *executable_node, t_shell *sh)
{
	char	**absolute_executables;
	int		i;
	char	*perfect_executable;

	i = 0;
	absolute_executables = get_absolute_executable(executable_node, sh);
	while(absolute_executables[i])
	{
		if (access(absolute_executables[i], X_OK) == 0)
		{
			perfect_executable = absolute_executables[i];
			return ; // i can have a struct for the execute part. and redir perfect executble to its struct.
		}
		i++;
	}
	printf("%s: command not found\n", executable_node->args[0]);
	sh->stop_iteration = 1;
}

//void	validate_redir(t_redir *red, t_shell *sh)
//{
//	
//}

/* print_loop(absolute_executables); */
void validate_tree(t_cmd *root, t_shell *sh)
{
	t_pipe *c;

	if (root->type == _EXEC && sh->stop_iteration == 0)
		validate_exec((t_exec *)root, sh);
	else if (root->type == _PIPE && sh->stop_iteration == 0)
	{
		c = (t_pipe *)root;
		validate_tree(c->left, sh);
		validate_tree(c->right, sh);
	}
	//else if (root->type == _REDIR)
	//	validate_redir((t_redir *)root, sh);
	/*  para redirect e cena complica pk n sei como ver s um ficheiro existe :/ tenho que ver isso. */
}