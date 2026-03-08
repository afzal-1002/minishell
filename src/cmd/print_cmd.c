#include "../includes/minishell.h"

void	print_cmd(t_cmd *cmd)
{
	char	**args;

	while (cmd)
	{
		args = cmd->args;
		ft_printf("Command: ");
		while (args && *args)
			ft_printf("%s ", *args++);
		ft_printf("\n");
		cmd = cmd->next;
	}
}
