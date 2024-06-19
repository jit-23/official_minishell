#ifndef ENV_H
#define ENV_H

#include "minishell.h"

typedef struct s_env t_env;
typedef struct s_shell t_shell;


struct s_env
{
    char *env_name;
    char *env_value;
    t_env *next;  
    t_env *prev;   
};

/* env_expand.c */

t_env *expand_env(t_shell *shell, char **env);
t_env *new_env_node(char *env); // prev e definido na funcao na qual este e chamada
char *get_name(char *env_var);
char *get_env_value(char *env_var);

#endif

