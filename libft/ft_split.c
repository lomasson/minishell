/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasson <lomasson@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 14:03:20 by lomasson          #+#    #+#             */
/*   Updated: 2022/06/24 11:47:01 by lomasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_lenght(const char *src, char c)
{
	int		i;
	int		y;
	char	**dest;

	i = 0;
	y = 0;
	while (src[i])
	{
		if (src[i] == c)
			i++;
		else
		{
			while (src[i] != c && src[i])
				i++;
			y++;
		}
	}
	dest = ft_calloc(y + 1, sizeof(char *));
	if (!dest)
		return (NULL);
	return (dest);
}

char	**ft_split(const char*s, char c)
{
	char	**dest;
	int		x;
	int		i;

	x = 0;
	if (!s)
		return (NULL);
	dest = ft_lenght(s, c);
	while (*s)
	{
		i = 0;
		if (*s == c)
			s++;
		else
		{
			while (*s != c && *s && s++)
				i++;
			dest[x] = ft_calloc(i + 1, sizeof(char));
			ft_strlcpy(dest[x++], s - i, i + 1);
		}
	}
	dest[x] = NULL;
	return (dest);
}
