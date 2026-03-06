#include "../includes/minishell.h"

void	env_append(t_global *global, t_env *node)
{
	t_env	*cur;

	if (!global->env)
	{
		global->env = node;
		return ;
	}
	cur = global->env;
	while (cur->next)
		cur = cur->next;
	cur->next = node;
}
