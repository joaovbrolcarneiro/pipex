/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_func.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrol-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 21:30:21 by jbrol-ca          #+#    #+#             */
/*   Updated: 2024/12/19 21:30:34 by jbrol-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr(char *str)
{
	int	i;

	i = 0;
	if (!str)
		str = "(null)";
	while (*str)
	{
		write(1, str, 1);
		str++;
		i++;
	}
	return (i);
}

int	ft_putnbr_hexa(unsigned int n, int cap)
{
	char	*hexa;
	int		count;

	count = 0;
	hexa = "0123456789abcdef";
	if (n < 16)
	{
		if (n > 9)
			count += ft_putchar(hexa[n] + cap);
		else
			count += ft_putchar(hexa[n]);
	}
	else
	{
		count += ft_putnbr_hexa(n / 16, cap);
		count += ft_putnbr_hexa(n % 16, cap);
	}
	return (count);
}

int	ft_putnbr(long number, int count)
{
	if (number < 0)
	{
		count += ft_putchar('-');
		number = -number;
	}
	if (number > 9)
	{
		count += ft_putnbr(number / 10, 0);
		count += ft_putchar(number % 10 + '0');
	}
	else
		count += ft_putchar(number + '0');
	return (count);
}

int	ft_ptr(unsigned long long ptr, int count)
{
	if (ptr == 0)
		return (write(1, "(nil)", 5));
	else
	{
		count += write(1, "0x", 2);
		count += ft_print_ptr(ptr, 0);
	}
	return (count);
}

int	ft_print_ptr(unsigned long long ptr, int count)
{
	char	*hexa;

	hexa = "0123456789abcdef";
	if (ptr < 16)
	{
		count += ft_putchar(hexa[ptr]);
	}
	else
	{
		count += ft_print_ptr(ptr / 16, 0);
		count += ft_putchar(hexa[ptr % 16]);
	}
	return (count);
}
