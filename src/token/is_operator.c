#include "../../includes/minishell.h"

 int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}
