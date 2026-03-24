/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolasze <mgolasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 19:00:35 by mgolasze          #+#    #+#             */
/*   Updated: 2025/03/06 19:36:32 by mgolasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_hex(unsigned int n, size_t *counter, char *base)
{
	if (n >= 16)
		ft_hex(n / 16, counter, base);
	ft_putchar(base[n % 16], counter);
}
