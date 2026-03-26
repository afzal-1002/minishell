/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafzal < mafzal@student.42warsaw.pl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 09:51:58 by mafzal            #+#    #+#             */
/*   Updated: 2026/03/26 20:36:26 by mafzal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	quit(t_global *global)
{
	int	exit_status;

	exit_status = global->exit_status;
	clear_history();
	free_all(global);
	exit(exit_status);
}
