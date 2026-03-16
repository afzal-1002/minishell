#include "../includes/minishell.h"

void	free_all(t_global *global)
{
	free_env(global->env);
	free_tokens(global->tokens);
	free_cmd(global->cmds);
	free(global);
}
