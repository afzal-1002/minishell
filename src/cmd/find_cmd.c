/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafzal < mafzal@student.42warsaw.pl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 09:49:37 by mafzal            #+#    #+#             */
/*   Updated: 2026/03/06 14:40:09 by mafzal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*build_full_path(char *dir, char *cmd)
{
	char	*slash;
	char	*result;

	slash = ft_strjoin(dir, "/");
	if (!slash)
		return (NULL);
	result = ft_strjoin(slash, cmd);
	free(slash);
	return (result);
}

char	*find_command(char *cmd, t_env *env)
{
	char	*path_val;
	char	**dirs;
	char	*full_path;
	int		i;

	if (!cmd || !cmd[0])
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	path_val = find_path_env(env);
	if (!path_val)
		return (NULL);
	dirs = ft_split(path_val, ':');
	if (!dirs)
		return (NULL);
	i = 0;
	while (dirs[i])
	{
		full_path = build_full_path(dirs[i], cmd);
		if (full_path && access(full_path, F_OK | X_OK) == 0)
		{
			free_array(dirs);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_array(dirs);
	return (NULL);
}
