/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafzal < mafzal@student.42warsaw.pl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 23:34:09 by mafzal            #+#    #+#             */
/*   Updated: 2026/02/22 23:39:56 by mafzal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_redirection(t_token_type type)
{
	if (type == T_REDIR_IN)
		return (1);
	if (type == T_REDIR_OUT)
		return (1);
	if (type == T_REDIR_APPEND)
		return (1);
	if (type == T_HEREDOC)
		return (1);
	if (type == T_FD_REDIR_OUT)
		return (1);
	if (type == T_FD_REDIR_APPEND)
		return (1);
	return (0);
}
