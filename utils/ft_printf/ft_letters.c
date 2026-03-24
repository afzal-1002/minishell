/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_letters.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolasze <mgolasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:40:06 by mgolasze          #+#    #+#             */
/*   Updated: 2025/03/06 19:47:22 by mgolasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putstr(char *c, size_t *counter)
{
	if (!c)
	{
		ft_putstr("(null)", counter);
		return ;
	}
	while (*c)
	{
		ft_putchar(*c, counter);
		c++;
	}
}
