/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafzal < mafzal@student.42warsaw.pl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 20:27:32 by mafzal            #+#    #+#             */
/*   Updated: 2026/03/16 22:42:07 by mafzal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*cmd_strappend(char *dst, const char *add)
{
	char	*joined;

	if (!dst)
		dst = ft_strdup("");
	if (!add)
		add = "";
	joined = ft_strjoin(dst, add);
	free(dst);
	return (joined);
}

void	expand_exit_status(int *i, char **out, t_global *global)
{
	char	*num;

	num = ft_itoa(global->exit_status);
	*out = cmd_strappend(*out, num);
	free(num);
	*i += 2;
}

char	*expand_word(const char *src, t_global *global)
{
	int		i;
	char	*out;

	i = 0;
	out = ft_strdup("");
	if (!out)
		return (NULL);
	while (src[i])
	{
		if (src[i] != '$')
			append_plain_char(src, &i, &out);
		else if (src[i + 1] == '?')
			expand_exit_status(&i, &out, global);
		else if (is_var_start(src[i + 1]))
			expand_env_var(src, &i, &out, global);
		else
		{
			out = cmd_strappend(out, "$");
			i++;
		}
	}
	return (out);
}
