/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasson <lomasson@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 11:05:46 by lomasson          #+#    #+#             */
/*   Updated: 2022/06/24 17:22:37 by lomasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	tmp;

	tmp = 0;
	if (!dst || !src)
		return (0);
	while (src[tmp])
		tmp++;
	if (!size)
		return (tmp);
	while (--size && *src)
		*dst++ = *src++;
	*dst = 0;
	return (tmp);
}
