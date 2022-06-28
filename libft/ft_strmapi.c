/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasson <lomasson@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 10:41:24 by lomasson          #+#    #+#             */
/*   Updated: 2022/06/24 17:22:43 by lomasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	int		j;
	char	*res;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
		i++;
	j = -1;
	res = malloc(sizeof(char) * (i + 1));
	if (!res)
		return (NULL);
	while (++j < i)
		res[j] = f(j, s[j]);
	res[j] = '\0';
	return (res);
}
