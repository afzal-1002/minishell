/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_operator_type.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafzal < mafzal@student.42warsaw.pl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 23:23:26 by mafzal            #+#    #+#             */
/*   Updated: 2026/02/23 00:01:14 by mafzal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <ctype.h>

t_token_type	get_operator_type(char *str, int i)
{
	if (isdigit(str[i]) && str[i + 1] == '>' && str[i + 2] == '>')
		return (T_FD_REDIR_APPEND);
	if (isdigit(str[i]) && str[i + 1] == '>')
		return (T_FD_REDIR_OUT);
	if (str[i] == '|')
		return (T_PIPE);
	if (str[i] == '<' && str[i + 1] && str[i + 1] == '<')
		return (T_HEREDOC);
	if (str[i] == '<')
		return (T_REDIR_IN);
	if (str[i] == '>' && str[i + 1] && str[i + 1] == '>')
		return (T_REDIR_APPEND);
	if (str[i] == '>')
		return (T_REDIR_OUT);
	return (T_WORD);
}
