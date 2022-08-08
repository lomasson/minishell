/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasson <lomasson@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:21:21 by lomasson          #+#    #+#             */
/*   Updated: 2022/08/08 19:30:47 by lomasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int	x;

	x = 0;
	if (!s1 || !s2)
		return (-1);
	while (n > 0)
	{
		if (s1[x] != s2[x] || !s1[x] || !s2[x])
			return (s1[x] - s2[x]);
		x++;
		n--;
	}
	return (0);
}
