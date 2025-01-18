/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrol-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 21:28:45 by jbrol-ca          #+#    #+#             */
/*   Updated: 2024/12/19 21:28:56 by jbrol-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	pf_verify(char c);
int	ft_putchar(int c);

int	pf_print(va_list *ap, char spec, int count)
{
	if (spec == 'c')
		count = ft_putchar(va_arg(*ap, int));
	else if (spec == '%')
		count = ft_putchar('%');
	else if (spec == 's')
		count = ft_putstr(va_arg(*ap, char *));
	else if (spec == 'i' || spec == 'd')
		count = ft_putnbr(va_arg(*ap, int), 0);
	else if (spec == 'u')
		count = ft_putnbr(va_arg(*ap, unsigned int), 0);
	else if (spec == 'x')
		count = ft_putnbr_hexa(va_arg(*ap, unsigned int), 0);
	else if (spec == 'X')
		count = ft_putnbr_hexa(va_arg(*ap, unsigned int), -32);
	else if (spec == 'p')
		count = ft_ptr(va_arg(*ap, unsigned long long), 0);
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		count;
	int		i;

	i = 0;
	count = 0;
	va_start(ap, format);
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1] && pf_verify(format[i + 1]))
		{
			count += pf_print(&ap, format[++i], 0);
		}
		else
			count += ft_putchar(format[i]);
		i++;
	}
	va_end(ap);
	return (count);
}

int	pf_verify(char c)
{
	char	*spec;

	spec = "cspdiuxX%";
	while (*spec)
	{
		if (*spec == c)
			return (1);
		spec++;
	}
	return (0);
}

int	ft_putchar(int c)
{
	return (write(1, &c, 1));
}
