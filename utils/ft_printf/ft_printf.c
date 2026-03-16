/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolasze <mgolasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:45:27 by mgolasze          #+#    #+#             */
/*   Updated: 2025/03/06 19:51:13 by mgolasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *cch, ...)
{
	va_list	cp;
	size_t	i;

	if (!cch)
		return (-1);
	va_start(cp, cch);
	i = 0;
	while (*cch)
	{
		if (*cch == '%')
		{
			cch++;
			ft_ifelse(*cch, cp, &i);
		}
		else
			ft_putchar(*cch, &i);
		cch++;
	}
	va_end(cp);
	return (i);
}
