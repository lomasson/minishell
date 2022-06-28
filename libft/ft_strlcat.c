/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 11:14:34 by lomasson          #+#    #+#             */
/*   Updated: 2022/02/27 19:32:49 by lomasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	size_t	x;
	size_t	l;
	size_t	i;

	i = 0;
	i = ft_strlen(dest);
	l = 0;
	while (src[l])
		l++;
	x = -1;
	if (i > n)
		return (n + l);
	if (*dest || *src)
	{
		while ((src[++x]) && (i + x + 1) < n)
			dest[i + x] = src[x];
		dest[x + i] = '\0';
	}
	return ((l + i));
}
