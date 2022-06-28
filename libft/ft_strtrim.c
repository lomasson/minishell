/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasson <lomasson@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 10:59:56 by lomasson          #+#    #+#             */
/*   Updated: 2022/06/24 17:22:58 by lomasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	find_right(char *src, char *sep)
{
	int	s;
	int	i;

	s = 0;
	i = 0;
	while (src[i + 1])
		i++;
	while (i >= 0 && sep[s])
	{
		if (sep[s] == src[i])
		{
			s = 0;
			i--;
		}
		else
			s++;
	}
	return (i);
}

int	find_left(char *src, char *sep)
{
	int	s;
	int	i;

	s = 0;
	i = 0;
	while (sep[s] && src[i])
	{
		if (sep[s] == src[i])
		{
			i++;
			s = 0;
		}
		else
			s++;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*dest;
	int		d;
	int		i;
	int		c;

	i = 0;
	d = 0;
	c = 0;
	i = find_left((char *)s1, (char *)set);
	c = find_right((char *)s1, (char *)set);
	if (!s1)
		return (NULL);
	if (c > 0)
		dest = (char *)malloc(c - i + 1);
	if (c <= 0)
		dest = (char *)malloc(1);
	if (!dest)
		return (NULL);
	while (i <= c)
		dest[d++] = s1[i++];
	dest[d] = '\0';
	return (dest);
}
