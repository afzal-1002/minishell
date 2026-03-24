/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafzal < mafzal@student.42warsaw.pl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 23:24:27 by mafzal            #+#    #+#             */
/*   Updated: 2026/03/24 22:31:32 by mafzal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	validate_redirection_syntax(t_token *current)
{
	char	*unexpected;

	if (!current->next)
		unexpected = "newline";
	else if (current->type == T_HEREDOC && current->next->type == T_REDIR_IN
		&& !current->next->next)
		unexpected = "newline";
	else if (is_redirection(current->next->type)
		|| current->next->type == T_PIPE)
	{
		if (current->next->value[0] == '<')
			unexpected = "<";
		else if (current->next->value[0] == '>')
			unexpected = ">";
		else
			unexpected = current->next->value;
	}
	else
		unexpected = NULL;
	return (token_error(unexpected));
}

static int	validate_token_syntax(t_token *tokens)
{
	t_token	*current;

	if (!tokens)
		return (1);
	current = tokens;
	if (current->type == T_PIPE)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		return (0);
	}
	while (current)
	{
		if (current->type == T_PIPE && (!current->next
				|| current->next->type == T_PIPE))
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `|'\n",
				2);
			return (0);
		}
		if (is_redirection(current->type)
			&& !validate_redirection_syntax(current))
			return (0);
		current = current->next;
	}
	return (1);
}

t_cmd	*parse_token(t_token *tokens, t_global *global)
{
	t_cmd	*head;
	t_cmd	*cmd;
	t_token	*current;

	if (!validate_token_syntax(tokens))
		return (NULL);
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
