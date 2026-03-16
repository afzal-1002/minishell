/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numbers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolasze <mgolasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:41:53 by mgolasze          #+#    #+#             */
/*   Updated: 2025/03/06 19:37:23 by mgolasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr_pf(int n, size_t *counter)
{
	if (n == -2147483648)
	{
		ft_putstr("-2147483648", counter);
		return ;
	}
	if (n < 0)
	{
		ft_putchar('-', counter);
		n = -n;
	}
	if (n >= 10)
	{
		ft_putnbr_pf(n / 10, counter);
	}
	ft_putchar(DIGITS[n % 10], counter);
}

void	ft_putuint_pf(unsigned int n, size_t *counter)
{
	if (n >= 10)
		ft_putuint_pf(n / 10, counter);
	ft_putchar(DIGITS[n % 10], counter);
}
