/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasson <lomasson@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 10:45:34 by lomasson          #+#    #+#             */
/*   Updated: 2022/06/24 17:22:30 by lomasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*tab;
	int		i;
	int		i1;

	i = 0;
	i1 = 0;
	while (s1[i])
		i++;
	while (s2[i1])
		i1++;
	tab = malloc(sizeof(char) * (i + i1 + 1));
	if (!tab)
		return (NULL);
	i = -1;
	i1 = 0;
	while (s1[++i])
		tab[i] = s1[i];
	while (s2[i1])
		tab[i++] = s2[i1++];
	tab[i] = '\0';
	return (tab);
}
