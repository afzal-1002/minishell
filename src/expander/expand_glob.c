/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_glob.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafzal < mafzal@student.42warsaw.pl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 16:00:00 by mafzal            #+#    #+#             */
/*   Updated: 2026/03/24 15:51:59 by mafzal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <dirent.h>
#include <fnmatch.h>

static int	contains_glob_chars(const char *str)
{
	while (*str)
	{
		if (*str == '*' || *str == '?' || *str == '[')
			return (1);
		str++;
	}
	return (0);
}

static int	match_pattern(const char *name, const char *pattern)
{
	return (fnmatch(pattern, name, FNM_PATHNAME) == 0);
}

char	**expand_glob_pattern(const char *pattern)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**matches;
	int				count;
	int				capacity;
	char			*dir_path;

	if (!contains_glob_chars(pattern))
		return (NULL);
	dir_path = ft_strdup(".");
	if (!dir_path)
		return (NULL);
	dir = opendir(dir_path);
	if (!dir)
	{
		free(dir_path);
		return (NULL);
	}
	matches = malloc(sizeof(char *) * 256);
	if (!matches)
	{
		closedir(dir);
		free(dir_path);
		return (NULL);
	}
	count = 0;
	capacity = 256;
	while ((entry = readdir(dir)) != NULL)
	{
		if (entry->d_name[0] == '.' && pattern[0] != '.')
			continue ;
		if (match_pattern(entry->d_name, pattern))
		{
			if (count >= capacity - 1)
			{
				capacity *= 2;
				matches = realloc(matches, sizeof(char *) * capacity);
				if (!matches)
				{
					closedir(dir);
					free(dir_path);
					return (NULL);
				}
			}
			matches[count] = ft_strdup(entry->d_name);
			if (!matches[count])
			{
				closedir(dir);
				free(dir_path);
				return (NULL);
			}
			count++;
		}
	}
	closedir(dir);
	free(dir_path);
	if (count == 0)
	{
		free(matches);
		return (NULL);
	}
	matches[count] = NULL;
	return (matches);
}
