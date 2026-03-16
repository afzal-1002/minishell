/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafzal < mafzal@student.42warsaw.pl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 21:59:23 by mafzal            #+#    #+#             */
/*   Updated: 2025/01/05 18:53:31 by mafzal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_wordcount(char const *s, char c)
{
	unsigned int	count;
	int				is_word;

	count = 0;
	is_word = 0;
	while (*s)
	{
		if (*s != c && !is_word)
		{
			count++;
			is_word = 1;
		}
		else if (*s == c)
			is_word = 0;
		s++;
	}
	return (count);
}

static char	*ft_extract_word(const char **s, char c)
{
	int		size;
	char	*word;
	int		i;

	size = 0;
	while (**s == c)
		(*s)++;
	while ((*s)[size] && (*s)[size] != c)
		size++;
	word = (char *)malloc((size + 1) * sizeof(char));
	if (!word)
		return (NULL);
	i = 0;
	while (i < size)
	{
		word[i] = (*s)[i];
		i++;
	}
	word[i] = '\0';
	*s += size;
	return (word);
}

static char	**ft_allocate_words(char const *s, char c, int words)
{
	char	**ptr;
	int		i;

	ptr = (char **)malloc((words + 1) * sizeof(char *));
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < words)
	{
		ptr[i] = ft_extract_word(&s, c);
		if (!ptr[i])
		{
			while (--i >= 0)
				free(ptr[i]);
			free(ptr);
			return (NULL);
		}
		i++;
	}
	ptr[i] = NULL;
	return (ptr);
}

char	**ft_split(char const *s, char c)
{
	int	words;

	if (!s)
		return (NULL);
	words = ft_wordcount(s, c);
	return (ft_allocate_words(s, c, words));
}
