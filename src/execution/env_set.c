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

t_env	*env_new_node(char *key, char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = ft_strdup(key);
	node->value = ft_strdup(value);
	node->next = NULL;
	if (!node->key || !node->value)
	{
		free(node->key);
		free(node->value);
		free(node);
		return (NULL);
	}
	return (node);
}

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

t_env	*env_set(t_global *global, char *key, char *value)
{
	t_env	*node;

	node = env_find(global->env, key);
	if (node)
	{
		env_update(node, value);
		return (0);
	}
	node = env_new_node(key, value);
	if (!node)
		return (0);
	env_append(global, node);
	return (node);
}
