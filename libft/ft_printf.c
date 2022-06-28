/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasson <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 10:24:46 by lomasson          #+#    #+#             */
/*   Updated: 2022/06/28 11:55:47 by lomasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_c(int c)
{
	return (write(1, &c, 1));
}

int	ft_printf_fonctions(int *j, char c, va_list *ap)
{
	int	count;

	j[0] = 8;
	count = 0;
	if (c == 'c')
		count = ft_print_c(va_arg(*ap, int));
	else if (c == 's')
		count = ft_print_s(va_arg(*ap, char *));
	else if (c == 'p')
		count = ft_print_ptr(va_arg(*ap, unsigned long int), 3, count);
	else if (c == 'd' || c == 'i')
		count = ft_print_num(va_arg(*ap, int), count);
	else if (c == 'u')
		count = ft_print_u(va_arg(*ap, unsigned int), count);
	else if (c == '%')
		count = write(1, "%", 1);
	else if (c == 'x')
		count = ft_print_hexa(va_arg(*ap, unsigned int), 0, count);
	else if (c == 'X')
		count = ft_print_hexa(va_arg(*ap, long int), 1, count);
	return (count);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		j[1];
	va_list	ap;
	char	*fcs;
	int		count;

	fcs = "cspdiu%xX";
	va_start(ap, str);
	i = -1;
	count = 0;
	while (str[++i])
	{
		j[0] = -1;
		if (str[i] == '%')
		{
			while (fcs[++j[0]] && str[i + 1])
				if (str[i + 1] == fcs[j[0]])
					count += ft_printf_fonctions(j, str[++i], &ap);
		}
		else
			count += write(1, &str[i], 1);
	}
	va_end(ap);
	return (count);
}
