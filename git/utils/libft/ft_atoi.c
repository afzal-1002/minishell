/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafzal < mafzal@student.42warsaw.pl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 17:58:39 by mafzal            #+#    #+#             */
/*   Updated: 2025/01/14 19:42:49 by mafzal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(char c)
{
	if (c == ' ' || c == '\f' || c == '\n' || c == '\r' || c == '\t'
		|| c == '\v')
		return (1);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	char	*ptr;
	int		i;
	int		neg;
	int		num;

	num = 0;
	neg = 1;
	ptr = (char *)nptr;
	i = 0;
	while (ft_isspace(ptr[i]) == 1)
		i++;
	if (ptr[i] == '-' || ptr[i] == '+')
	{
		if (ptr[i] == '-')
			neg = -1;
		i++;
	}
	while ((ptr[i] >= '0' && ptr[i] <= '9') && ptr[i] != '\0')
	{
		num = (num * 10) + (ptr[i] - '0');
		i++;
	}
	return (num * neg);
}
