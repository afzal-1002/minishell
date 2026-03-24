/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_glob.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafzal < mafzal@student.42warsaw.pl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 16:00:00 by mafzal            #+#    #+#             */
/*   Updated: 2026/03/24 19:55:51 by mafzal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <dirent.h>

#define GLOB_START_CAP 32

static int	contains_glob_chars(const char *str)
{
	while (*str)
	{
		if (*str == '*' || *str == '?')
			return (1);
		str++;
	}
	return (0);
}

static void	free_partial(char **arr, int count)
{
	while (count > 0)
	{
		count--;
		free(arr[count]);
	}
	free(arr);
}

static int	append_match(char ***matches, int *count, int *capacity, char *name)
{
	char	**new_arr;
	int		new_capacity;
	int		i;

	if (*count >= *capacity - 1)
	{
		new_capacity = (*capacity * 2);
		new_arr = malloc(sizeof(char *) * new_capacity);
		if (!new_arr)
			return (0);
		i = 0;
		while (i < *count)
		{
			new_arr[i] = (*matches)[i];
			i++;
		}
		free(*matches);
		*matches = new_arr;
		*capacity = new_capacity;
	}
	(*matches)[*count] = ft_strdup(name);
	if (!(*matches)[*count])
		return (0);
	(*count)++;
	return (1);
}

static int	read_matches(DIR *dir, const char *pattern, char ***matches,
		int *count)
{
	struct dirent	*entry;
	int				capacity;

	capacity = GLOB_START_CAP;
	while (1)
	{
		entry = readdir(dir);
		if (!entry)
			break ;
		if (entry->d_name[0] == '.' && pattern[0] != '.')
			continue ;
		if (!glob_match_pattern(pattern, entry->d_name))
			continue ;
		if (!append_match(matches, count, &capacity, entry->d_name))
			return (0);
	}
	return (1);
}

char	**expand_glob_pattern(const char *pattern)
{
	DIR		*dir;
	char	**matches;
	int		count;

	if (!contains_glob_chars(pattern))
		return (NULL);
	dir = opendir(".");
	if (!dir)
		return (NULL);
	matches = malloc(sizeof(char *) * GLOB_START_CAP);
	if (!matches)
		return (closedir(dir), NULL);
	count = 0;
	if (!read_matches(dir, pattern, &matches, &count))
		return (closedir(dir), free_partial(matches, count), NULL);
	closedir(dir);
	if (count == 0)
		return (free(matches), NULL);
	matches[count] = NULL;
	return (matches);
}
