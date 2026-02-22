/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafzal < mafzal@student.42warsaw.pl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 23:37:15 by mafzal            #+#    #+#             */
/*   Updated: 2026/02/22 23:42:40 by mafzal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd	*handle_pipe(t_cmd *cmd)
{
	t_cmd	*new_cmd;

	new_cmd = create_cmd();
	if (!new_cmd)
		return (NULL);
	new_cmd->index = cmd->index + 1;
	cmd->next = new_cmd;
	return (new_cmd);
}
