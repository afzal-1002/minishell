/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolasze <mgolasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:42:52 by mgolasze          #+#    #+#             */
/*   Updated: 2026/03/11 18:01:51 by mgolasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

# define HEX_UPP_BASE "0123456789ABCDEF"
# define HEX_LOW_BASE "0123456789abcdef"
# define DIGITS "0123456789"

int		ft_printf(const char *cch, ...);
void	ft_putnbr_pf(int n, size_t *counter);
void	ft_putuint_pf(unsigned int n, size_t *counter);
void	ft_ifelse(char specifier, va_list args, size_t *counter);
void	ft_putstr(char *c, size_t *counter);
void	ft_pointer(void *pointer, size_t *counter);
void	ft_putchar(char c, size_t *counter);
void	ft_hex(unsigned int n, size_t *counter, char *base);
void	ft_puthex_address(unsigned long n, size_t *counter, char *base);

#endif