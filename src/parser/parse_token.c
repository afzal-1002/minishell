/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafzal < mafzal@student.42warsaw.pl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 23:24:27 by mafzal            #+#    #+#             */
/*   Updated: 2026/03/17 23:34:28 by mafzal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	add_expanded_arg(t_cmd *cmd, t_token *current, t_global *global)
{
	char	*expanded;

	expanded = expand_word(current->value, global, current->type);
	if (!expanded)
		return (0);
	add_cmd_arg(cmd, expanded);
	free(expanded);
	return (1);
}

int	check_token(t_token **current, t_cmd **cmd, t_cmd *head, t_global *global)
{
	if ((*current)->type == T_WORD || (*current)->type == T_SINGLE_QUOTE
		|| (*current)->type == T_DOUBLE_QUOTE)
	{
		if (!add_expanded_arg(*cmd, *current, global))
		{
			free_cmd(head);
			return (0);
		}
	}
	else if (is_redirection((*current)->type))
		*current = handle_redirection(*cmd, *current);
	else if ((*current)->type == T_PIPE)
		*cmd = handle_pipe(*cmd);
	return (1);
}

t_cmd	*parse_token(t_token *tokens, t_global *global)
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
		if (!check_token(&current, &cmd, head, global))
			return (NULL);
		current = current->next;
	}
	return (head);
}
