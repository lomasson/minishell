/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasson <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 18:09:02 by lomasson          #+#    #+#             */
/*   Updated: 2022/03/10 11:58:11 by lomasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count(long int nb)
{
	long int	c;
	long int	minus;

	minus = 0;
	if (nb < 0)
	{
		nb *= -1;
		minus = 1;
	}
	if (nb < 10 && nb >= 0)
		return (1 + minus);
	if (nb >= 10)
	{
		c = count(nb / 10);
		return (1 + c + minus);
	}
	return (0);
}

char	*ft_itoa(int n)
{
	long int	nb;
	int			i;
	char		*res;

	nb = n;
	i = count(nb);
	res = ft_calloc((i + 1), sizeof(char));
	if (!res)
		return (NULL);
	if (nb < 0)
	{
		nb *= -1;
		res[0] = '-';
	}
	i--;
	while (nb >= 10)
	{
		res[i] = (nb % 10) + '0';
		nb = nb / 10;
		i--;
	}
	res[i] = nb + '0';
	return (res);
}
