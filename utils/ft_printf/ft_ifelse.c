/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ifelse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolasze <mgolasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 19:24:51 by mgolasze          #+#    #+#             */
/*   Updated: 2025/03/06 19:33:47 by mgolasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_ifelse(char specifier, va_list args, size_t *counter)
{
	if (specifier == 'c')
		ft_putchar(va_arg(args, int), counter);
	else if (specifier == 's')
		ft_putstr(va_arg(args, char *), counter);
	else if (specifier == 'p')
		ft_pointer(va_arg(args, void *), counter);
	else if (specifier == 'i' || specifier == 'd')
		ft_putnbr_pf(va_arg(args, int), counter);
	else if (specifier == 'u')
		ft_putuint_pf(va_arg(args, unsigned int), counter);
	else if (specifier == 'X')
		ft_hex(va_arg(args, unsigned int), counter, HEX_UPP_BASE);
	else if (specifier == 'x')
		ft_hex(va_arg(args, unsigned int), counter, HEX_LOW_BASE);
	else if (specifier == '%')
		ft_putchar('%', counter);
}
