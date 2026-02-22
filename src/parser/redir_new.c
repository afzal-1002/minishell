/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafzal < mafzal@student.42warsaw.pl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 23:24:21 by mafzal            #+#    #+#             */
/*   Updated: 2026/02/22 23:46:34 by mafzal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	redir_new(t_cmd *cmd, t_token_type type, char *op, char *value)
{
	t_redir	*new;

	new = malloc(sizeof(t_redir));
	if (!new)
		return ;
	new->type = type;
	new->file = ft_strdup(value);
	new->next = NULL;
	if ((type == T_FD_REDIR_OUT || type == T_FD_REDIR_APPEND) && isdigit(op[0]))
	{
		new->fd = op[0] - '0';
	}
	else if (type == T_REDIR_IN || type == T_HEREDOC)
		new->fd = 0;
	else
		new->fd = 1;
	redir_add_back(&cmd->redirs, new);
}
