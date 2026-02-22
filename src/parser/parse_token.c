/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafzal < mafzal@student.42warsaw.pl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 23:24:27 by mafzal            #+#    #+#             */
/*   Updated: 2026/02/22 23:45:33 by mafzal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd	*parse_token(t_token *tokens)
{
	t_cmd	*head;
	t_cmd	*cmd;
	t_token	*current;

	head = create_cmd();
	if (!head)
		return (NULL);
	cmd = head;
	current = tokens;
	while (current)
	{
		if (current->type == T_WORD)
			add_arg(cmd, current->value);
		else if (is_redirection(current->type))
			current = handle_redirection(cmd, current);
		else if (current->type == T_PIPE)
			cmd = handle_pipe(cmd);
		current = current->next;
	}
	return (head);
}
