/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adapassa <adapassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 10:21:31 by adapassa          #+#    #+#             */
/*   Updated: 2024/01/16 10:41:51 by adapassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <stdarg.h>
# include <stdio.h>
# include <unistd.h>

# define TRUE 1
# define FALSE 0

int	ft_printf(const char *format, ...);
int	ft_print_unsinged(unsigned long n);
int	ft_printptr(unsigned long address);
int	ft_putnbr(int n);
int	ft_printhex(unsigned long nbr, int maiusc);
int	ft_putstr(char *str);
int	ft_putchar(char c);

#endif
