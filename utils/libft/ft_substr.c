/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafzal < mafzal@student.42warsaw.pl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 14:58:30 by mafzal            #+#    #+#             */
/*   Updated: 2025/01/10 14:29:07 by mafzal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_substrlen(char const *str, unsigned int start, size_t len)
{
	size_t	count;

	count = 0;
	if (str == NULL || start >= ft_strlen(str))
		return (0);
	while (str[start] != '\0' && len > count)
	{
		start++;
		count++;
	}
	return (count);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	strlen;
	size_t	i;

	if (s == NULL)
		return (NULL);
	strlen = ft_substrlen(s, start, len);
	ptr = (char *)malloc((strlen + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		ptr[0] = '\0';
		return (ptr);
	}
	i = 0;
	while (s[start] != '\0' && i < len)
	{
		ptr[i] = s[start];
		i++;
		start++;
	}
	ptr[i] = '\0';
	return (ptr);
}
