#include "../includes/minishell.h"

void	expand_env_var(const char *src, int *i, char **out, t_global *g)
{
	int		start;
	char	*piece;
	char	*num;

	start = ++(*i);
	while (src[*i] && is_var_char(src[*i]))
		(*i)++;
	piece = ft_substr(src, start, *i - start);
	num = env_value_or_empty(g, piece);
	*out = cmd_strappend(*out, num);
	free(piece);
	free(num);
}
