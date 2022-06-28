/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasson <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 14:16:48 by lomasson          #+#    #+#             */
/*   Updated: 2022/06/13 19:40:10 by lomasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *src)
{
	int		i;
	int		minus;
	int		rvalue;
	char	*str;

	str = (char *)src;
	i = 0;
	minus = 0;
	rvalue = 0;
	while (str[i] == 32 || str[i] == 9 || str[i] == 10
		|| str[i] == 11 || str[i] == 12 || str[i] == 13)
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			minus++;
	while (str[i] >= 48 && str[i] <= 57)
		rvalue = (rvalue * 10) + (str[i++] - 48);
	if (minus != 0)
		rvalue = -rvalue;
	return (rvalue);
}
