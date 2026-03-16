/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pointer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolasze <mgolasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 18:45:56 by mgolasze          #+#    #+#             */
/*   Updated: 2025/03/06 19:37:21 by mgolasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_puthex_address(unsigned long n, size_t *counter, char *base)
{
	if (n >= 16)
		ft_puthex_address(n / 16, counter, base);
	ft_putchar(base[n % 16], counter);
}

void	ft_pointer(void *pointer, size_t *counter)
{
	unsigned long	address;

	if (!pointer)
	{
		ft_putstr("(nil)", counter);
		return ;
	}
	address = (unsigned long)pointer;
	ft_putstr("0x", counter);
	ft_puthex_address(address, counter, HEX_LOW_BASE);
}
