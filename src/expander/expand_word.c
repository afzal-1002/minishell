/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolasze <mgolasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 20:27:32 by mafzal            #+#    #+#             */
/*   Updated: 2026/03/23 18:12:34 by mgolasze         ###   ########.fr       */
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

static void	update_quote(t_expander *expander)
{
	char	c;

	c = expander->src[expander->i];
	if (c == '\'' && !expander->is_doublequote)
		expander->is_singlequote = !expander->is_singlequote;
	else if (c == '"' && !expander->is_singlequote)
		expander->is_doublequote = !expander->is_doublequote;
	expander->i++;
}

static void	handle_dollar(t_expander *expander)
{
	if (expander->is_singlequote)
		append_plain_char(expander->src, &expander->i, &expander->out);
	else if (expander->src[expander->i + 1] == '?')
		expand_exit_status(&expander->i, &expander->out, expander->global);
	else if (is_var_start(expander->src[expander->i + 1]))
		expand_env_var(expander->src, &expander->i,
			&expander->out, expander->global);
	else
	{
		expander->out = cmd_strappend(expander->out, "$");
		expander->i++;
	}
}

char	*expand_word(const char *src, t_global *global)
{
	t_expander	expander;

	expander.global = global;
	expander.i = 0;
	expander.is_singlequote = 0;
	expander.is_doublequote = 0;
	expander.src = (char *)src;
	expander.out = ft_strdup("");
	if (!expander.out)
		return (NULL);
	while (expander.src[expander.i])
	{
		if (expander.src[expander.i] == '\'' || expander.src[expander.i] == '"')
			update_quote(&expander);
		else if (expander.src[expander.i] == '$')
			handle_dollar(&expander);
		else
			append_plain_char(expander.src, &expander.i, &expander.out);
	}
	return (expander.out);
}
