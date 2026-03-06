/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafzal < mafzal@student.42warsaw.pl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 23:24:15 by mafzal            #+#    #+#             */
/*   Updated: 2026/03/06 15:53:52 by mafzal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_global	global;

	(void)argc;
	(void)argv;
	createglobal(&global, envp);
	init_shell(&global);
	return (0);
}
