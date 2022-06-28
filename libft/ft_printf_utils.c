/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasson <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 21:58:54 by lomasson          #+#    #+#             */
/*   Updated: 2022/06/28 11:55:25 by lomasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_hexa(unsigned int n, int u, int count)
{
	char	c;

	if (n >= 16)
	{
		count = ft_print_hexa(n / 16, u, count);
		count = ft_print_hexa(n % 16, u, count);
	}
	if (n < 16)
	{
		if (n >= 10 && n <= 15 && u == 0)
			c = (n - 10) + 'a';
		else if (n >= 10 && n <= 15 && u == 1)
			c = (n - 10) + 'A';
		else
			c = '0' + n;
		count += write(1, &c, 1);
	}
	return (count);
}

int	ft_print_num(long int n, int count)
{
	char	c;

	if (n == LONG_MIN)
		return (write(1, "-9223372036854775808", 20));
	if (n < 0)
	{
		count = write(1, "-", 1);
		n = -n;
		count = ft_print_num(n, count);
	}
	else if (n >= 10)
	{
		count = ft_print_num(n / 10, count);
		count = ft_print_num(n % 10, count);
	}
	else if (n < 10)
	{
		c = '0' + n;
		count += write(1, &c, 1);
	}
	return (count);
}

int	ft_print_ptr(unsigned long int n, int u, int count)
{
	char	c;

	if (u == 3)
	{
		count += write(1, "0x", 2);
		u = 0;
	}
	if (n >= 16)
	{
		count = ft_print_ptr(n / 16, u, count);
		count = ft_print_ptr(n % 16, u, count);
	}
	if (n < 16)
	{
		if (n >= 10 && n <= 15)
			c = (n - 10) + 'a';
		else
			c = '0' + n;
		count += write(1, &c, 1);
	}
	return (count);
}

int	ft_print_s(char *str)
{
	int	count;
	int	len;

	len = 0;
	count = 0;
	if (!str)
		return (write(1, "(null)", 6));
	while (str[len])
		count += write(1, &str[len++], 1);
	return (count);
}

int	ft_print_u(unsigned int n, int count)
{
	char	c;

	if (n >= 10)
	{
		count = ft_print_num(n / 10, count);
		count = ft_print_num(n % 10, count);
	}
	else if (n < 10)
	{
		c = '0' + n;
		count += write(1, &c, 1);
	}
	return (count);
}
