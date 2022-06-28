/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasson <lomasson@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 17:55:10 by lomasson          #+#    #+#             */
/*   Updated: 2022/06/24 17:23:31 by lomasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	int				x;
	unsigned char	*src;
	unsigned char	*src2;

	src = (unsigned char *)s1;
	src2 = (unsigned char *)s2;
	x = 0;
	while (n > 0)
	{
		if (*src != *src2)
			return (*src - *src2);
		n--;
		src++;
		src2++;
	}
	return (0);
}
