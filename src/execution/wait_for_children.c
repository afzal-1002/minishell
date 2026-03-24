/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_for_children.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolasze <mgolasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 14:40:22 by mafzal            #+#    #+#             */
/*   Updated: 2026/03/16 17:48:17 by mgolasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	wait_for_children(t_global *global)
{
	int	status;
	int	last;

	last = 0;
	while (wait(&status) > 0)
	{
		if (WIFEXITED(status))
			last = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			last = 128 + WTERMSIG(status);
	}
	global->exit_status = last;
}
