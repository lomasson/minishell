/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasson <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 10:24:07 by lomasson          #+#    #+#             */
/*   Updated: 2022/03/10 09:33:32 by lomasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*src;
	char	*dest;

	src = (char *)s;
	if (!src)
		return (NULL);
	if (ft_strlen(s) < len)
		dest = (char *) malloc(ft_strlen(s) + 1);
	else
		dest = (char *) malloc(len + 1);
	if (!dest)
		return (NULL);
		src = src + start;
	if (ft_strlen(s) >= start)
		ft_strlcpy(dest, src, len + 1);
	else
		dest[0] = '\0';
	return (dest);
}
