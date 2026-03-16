/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafzal < mafzal@student.42warsaw.pl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 14:33:24 by mafzal            #+#    #+#             */
/*   Updated: 2025/01/14 19:43:23 by mafzal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_nums(int num)
{
	int	length;

	length = 0;
	if (num <= 0)
		length = 1;
	while (num != 0)
	{
		num /= 10;
		length++;
	}
	return (length);
}

static int	ft_isnegative(int num)
{
	int	neg;

	neg = 0;
	if (num < 0)
		neg = 1;
	return (neg);
}

char	*ft_itoa(int n)
{
	long	num;
	int		negative;
	int		length;
	char	*str;

	num = n;
	negative = ft_isnegative(num);
	length = ft_count_nums(n) + 1;
	str = (char *)malloc(length * sizeof(char));
	if (!str)
		return (NULL);
	str[--length] = '\0';
	if (negative == 1)
		num = -num;
	while (--length >= 0)
	{
		str[length] = (num % 10) + '0';
		num /= 10;
		if (negative && length == 0)
			str[length] = '-';
	}
	return (str);
}
