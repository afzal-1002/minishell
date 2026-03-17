/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utilits.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafzal < mafzal@student.42warsaw.pl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 23:24:09 by mafzal            #+#    #+#             */
/*   Updated: 2026/03/16 23:27:10 by mafzal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_var_start(char c)
{
	return (ft_isalpha(c) || c == '_');
}

int	is_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}
