/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolasze <mgolasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 09:49:13 by mafzal            #+#    #+#             */
/*   Updated: 2026/03/23 18:35:25 by mgolasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	split_key_value(char *arg, char **key, char **value)
{
	char	*eq;
	int		key_len;

	eq = ft_strchr(arg, '=');
	if (!eq)
	{
		*key = ft_strdup(arg);
		*value = NULL;
	}
	else
	{
		key_len = eq - arg;
		*key = ft_substr(arg, 0, key_len);
		*value = eq + 1;
	}
	if (!*key)
		return (-1);
	return (0);
}

void	export_print_all(t_global *global)
{
	t_env	*cur;

	cur = global->env;
	while (cur)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(cur->key, STDOUT_FILENO);
		if (cur->value)
		{
			ft_putstr_fd("=\"", STDOUT_FILENO);
			ft_putstr_fd(cur->value, STDOUT_FILENO);
			ft_putstr_fd("\"", STDOUT_FILENO);
		}
		ft_putstr_fd("\n", STDOUT_FILENO);
		cur = cur->next;
	}
}

int	export_one(char *arg, t_global *global)
{
	char	*key;
	char	*value;

	if (split_key_value(arg, &key, &value) == -1)
		return (1);
	if (!is_valid_identifier(key))
	{
		ft_putstr_fd("export: `", STDERR_FILENO);
		ft_putstr_fd(key, STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
		free(key);
		return (1);
	}
	env_set(global, key, value);
	free(key);
	return (0);
}

int	builtin_export(t_cmd *cmd, t_global *global)
{
	int	i;
	int	ret;

	if (!cmd->args[1])
	{
		export_print_all(global);
		return (0);
	}
	ret = 0;
	i = 1;
	while (cmd->args[i])
	{
		if (export_one(cmd->args[i], global) != 0)
			ret = 1;
		i++;
	}
	return (ret);
}
