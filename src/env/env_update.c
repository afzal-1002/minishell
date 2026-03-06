#include "../includes/minishell.h"

void	env_update(t_env *node, char *value)
{
	char	*new_val;

	new_val = ft_strdup(value);
	if (!new_val)
		return ;
	free(node->value);
	node->value = new_val;
}
