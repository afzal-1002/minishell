/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolasze <mgolasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 23:36:16 by mafzal            #+#    #+#             */
/*   Updated: 2026/03/23 20:21:20 by mgolasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*handle_redirection(t_cmd *cmd, t_token *current, t_global *global)
{
	char	*filename;

	if (current->next && current->next->type == T_WORD)
	{
		if (current->type == T_HEREDOC)
			filename = ft_strdup(current->next->value);
		else
			filename = expand_word(current->next->value, global);
		redir_new(cmd, current->type, current->value, filename);
		free(filename);
		return (current->next);
	}
	return (current);
}
