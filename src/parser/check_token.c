/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafzal < mafzal@student.42warsaw.pl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 22:21:56 by mafzal            #+#    #+#             */
/*   Updated: 2026/03/24 22:26:38 by mafzal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_token(t_token **current, t_cmd **cmd, t_cmd *head, t_global *global)
{
	if ((*current)->type == T_WORD)
	{
		if (!add_expanded_arg(*cmd, *current, global))
		{
			free_cmd(head);
			return (0);
		}
	}
	else if (is_redirection((*current)->type))
		*current = handle_redirection(*cmd, *current, global);
	else if ((*current)->type == T_PIPE)
		*cmd = handle_pipe(*cmd);
	return (1);
}
