/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_type_name.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafzal < mafzal@student.42warsaw.pl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 23:24:02 by mafzal            #+#    #+#             */
/*   Updated: 2026/02/22 23:24:03 by mafzal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_type_name(t_token_type type)
{
	if (type == T_WORD)
		return ("WORD");
	if (type == T_PIPE)
		return ("PIPE");
	if (type == T_REDIR_IN)
		return ("REDIR_IN");
	if (type == T_REDIR_OUT)
		return ("REDIR_OUT");
	if (type == T_REDIR_APPEND)
		return ("APPEND");
	if (type == T_HEREDOC)
		return ("HEREDOC");
	if (type == T_FD_REDIR_OUT)
		return ("FD_REDIR_OUT");
	if (type == T_FD_REDIR_APPEND)
		return ("FD_REDIR_APPEND");
	return ("UNKNOWN");
}
