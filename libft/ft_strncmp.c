/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasson <lomasson@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:21:21 by lomasson          #+#    #+#             */
/*   Updated: 2022/08/02 12:00:33 by lomasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int	x;

	x = -1;
	if (!s1 || !s2)
		return (-1);
	while (n > 0)
	{
		if (*s1 != *s2 || !s1 || !s2)
			return ((char)*s1 - (char)*s2);
		s1++;
		s2++;
		n--;
	}
	return (0);
}
