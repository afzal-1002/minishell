/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolasze <mgolasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 18:08:30 by mgolasze          #+#    #+#             */
/*   Updated: 2026/03/23 18:12:56 by mgolasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	expand_exit_status(int *i, char **out, t_global *global)
{
	char	*num;

	num = ft_itoa(global->exit_status);
	*out = cmd_strappend(*out, num);
	free(num);
	*i += 2;
}
