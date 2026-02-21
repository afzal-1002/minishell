#include "includes/minishell.h"

int	main(void)
{
	char	*input;
	t_token	*tokens;
	t_cmd	*parsed_cmd;
	int		i;
	t_redir	*redirs;

	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (*input)
			add_history(input);
		tokens = tokenize(input);
		printf("\n--- TOKENS ---\n");
		print_tokens(tokens);
		printf("--------------\n\n");
		parsed_cmd = parse_token(tokens);
		if (parsed_cmd)
		{
			printf("Parsed Command:\n");
			while (parsed_cmd)
			{
				printf("  Command: %d\n", parsed_cmd->index);
				if (parsed_cmd->args)
				{
					i = 0;
					while (parsed_cmd->args[i])
					{
						printf("  Arg[%d]: %s\n", i, parsed_cmd->args[i]);
						i++;
					}
				}
				redirs = parsed_cmd->redirs;
				while (redirs)
				{
					printf("  Redirection: %s -> %s\n",
						get_type_name(redirs->type), redirs->file);
					redirs = redirs->next;
				}
				parsed_cmd = parsed_cmd->next;
			}
			printf("\n");
		}
		free_tokens(tokens);
		free_cmd(parsed_cmd);
		free(input);
	}
	return (0);
}
