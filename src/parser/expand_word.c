/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafzal < mafzal@student.42warsaw.pl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 20:27:32 by mafzal            #+#    #+#             */
/*   Updated: 2026/03/17 23:37:04 by mafzal           ###   ########.fr       */
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

char	*expand_exit_status(int *i, t_global *global)
{
	char	*num;

	num = ft_itoa(global->exit_status);
	*i += 2;
	return (num);
}

char	*expand_word(const char *src, t_global *global, t_token_type type)
{
	int		i;
	char	*out;
	char	*temp;

	i = 0;
	out = ft_strdup("");
	if (!out)
		return (NULL);
	if (type == T_SINGLE_QUOTE)
	{
		temp = ft_strdup(src);
		return (temp);
	}
	while (src[i])
	{
		if (src[i] != '$')
		{
			temp = append_plain_char(src, &i);
			out = cmd_strappend(out, temp);
			free(temp);
		}
		else if (src[i + 1] == '?')
		{
			temp = expand_exit_status(&i, global);
			out = cmd_strappend(out, temp);
			free(temp);
		}
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
