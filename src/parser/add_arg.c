#include "../../includes/minishell.h"

void	add_arg(t_cmd *cmd, char *value)
{
	char **new_args;
	int i;

	i = 0;
	while (cmd->args && cmd->args[i])
		i++;

	new_args = malloc(sizeof(char *) * (i + 2));
	if (!new_args)
		return ;

	i = 0;
	while (cmd->args && cmd->args[i])
	{
		new_args[i] = cmd->args[i];
		i++;
	}
	new_args[i] = strdup(value);
	new_args[i + 1] = NULL;

	free(cmd->args);
	cmd->args = new_args;
}