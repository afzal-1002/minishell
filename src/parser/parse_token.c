/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafzal < mafzal@student.42warsaw.pl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 23:24:27 by mafzal            #+#    #+#             */
/*   Updated: 2026/03/24 16:13:23 by mafzal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	has_quotes(const char *str)
{
	while (*str)
	{
		if (*str == '\'' || *str == '"')
			return (1);
		str++;
	}
	return (0);
}

static int	validate_token_syntax(t_token *tokens)
{
	t_token	*current;
	char	*unexpected;

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
		if (is_redirection(current->type))
		{
			if (!current->next)
				unexpected = "newline";
			else if (current->type == T_HEREDOC
				&& current->next->type == T_REDIR_IN && !current->next->next)
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
			if (unexpected)
			{
				ft_putstr_fd("minishell: syntax error near unexpected token `",
					2);
				ft_putstr_fd(unexpected, 2);
				ft_putstr_fd("'\n", 2);
				return (0);
			}
		}
		current = current->next;
	}
	return (1);
}

int	add_expanded_arg(t_cmd *cmd, t_token *current, t_global *global)
{
	char	*expanded;
	char	**glob_matches;
	int		index;

	expanded = expand_word(current->value, global);
	if (!expanded)
		return (0);
	if (!has_quotes(current->value))
	{
		glob_matches = expand_glob_pattern(expanded);
		if (glob_matches)
		{
			index = 0;
			while (glob_matches[index])
			{
				add_cmd_arg(cmd, glob_matches[index]);
				free(glob_matches[index]);
				index++;
			}
			free(glob_matches);
		}
		else
			add_cmd_arg(cmd, expanded);
	}
	else
		add_cmd_arg(cmd, expanded);
	free(expanded);
	return (1);
}

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
