#include "../includes/minishell.h"

void	env_remove(t_global *global, char *key)
{
	t_env	*cur;
	t_env	*prev;

	cur = global->env;
	prev = NULL;
	while (cur)
	{
		if (ft_strncmp(cur->key, key, ft_strlen(key) + 1) == 0)
		{
			if (prev)
				prev->next = cur->next;
			else
				global->env = cur->next;
			free(cur->key);
			free(cur->value);
			free(cur);
			return ;
		}
		prev = cur;
		cur = cur->next;
	}
}