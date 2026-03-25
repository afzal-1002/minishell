/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_expanded_arg.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafzal < mafzal@student.42warsaw.pl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 22:24:24 by mafzal            #+#    #+#             */
/*   Updated: 2026/03/24 22:26:02 by mafzal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	add_and_free_glob_matches(t_cmd *cmd, char **glob_matches)
{
	int	index;

	index = 0;
	while (glob_matches[index])
	{
		add_cmd_arg(cmd, glob_matches[index]);
		free(glob_matches[index]);
		index++;
	}
	free(glob_matches);
}

int	add_expanded_arg(t_cmd *cmd, t_token *current, t_global *global)
{
	char	*expanded;
	char	**glob_matches;

	expanded = expand_word(current->value, global);
	if (!expanded)
		return (0);
	if (!has_quotes(current->value))
	{
		glob_matches = expand_glob_pattern(expanded);
		if (glob_matches)
			add_and_free_glob_matches(cmd, glob_matches);
		else
			add_cmd_arg(cmd, expanded);
	}
	else
		add_cmd_arg(cmd, expanded);
	free(expanded);
	return (1);
}
