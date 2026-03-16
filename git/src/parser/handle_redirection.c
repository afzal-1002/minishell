/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafzal < mafzal@student.42warsaw.pl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 23:36:16 by mafzal            #+#    #+#             */
/*   Updated: 2026/02/23 00:12:56 by mafzal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*handle_redirection(t_cmd *cmd, t_token *current)
{
	if (current->next && current->next->type == T_WORD)
	{
		redir_new(cmd, current->type, current->value, current->next->value);
		return (current->next);
	}
	return (current);
}
