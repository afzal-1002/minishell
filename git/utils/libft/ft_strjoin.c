/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafzal < mafzal@student.42warsaw.pl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 17:00:28 by mafzal            #+#    #+#             */
/*   Updated: 2025/01/05 18:53:33 by mafzal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_append_to_ptr(char *dest, const char *src, size_t i)
{
	while (src && *src)
	{
		dest[i] = *src;
		i++;
		src++;
	}
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	size_t	strlen1;
	size_t	strlen2;
	size_t	i;

	if (!s1 || !s2)
		return (NULL);
	strlen1 = ft_strlen(s1);
	strlen2 = ft_strlen(s2);
	ptr = (char *)malloc((strlen1 + strlen2 + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	if (s1)
		i = ft_append_to_ptr(ptr, s1, i);
	if (s2)
		i = ft_append_to_ptr(ptr, s2, i);
	ptr[i] = '\0';
	return (ptr);
}
