/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_commande.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasson <lomasson@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 13:49:03 by chajjar           #+#    #+#             */
/*   Updated: 2022/08/08 14:52:46 by lomasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_get(char *s1, char *s2)
{
	size_t	i;
	size_t	len1;
	char	*str;

	if (s1 && s2)
	{
		len1 = ft_strlen(s1);
		str = (char *)malloc(sizeof(char) * (len1 + ft_strlen(s2) + 1));
		if (str == NULL)
			return (NULL);
		i = -1;
		while (s1[++i])
			str[i] = s1[i];
		i = -1;
		while (s2[++i])
		{
			str[len1] = s2[i];
			len1++;
		}
		str[len1] = '\0';
		free(s1);
		free(s2);
		return (str);
	}
	return (NULL);
}

char	*occurent(char *str, int (*condition)(char *))
{
	char	*ptr;
	int		quote;

	quote = 0;
	ptr = (char *)str;
	while (*ptr != '\0')
	{
		check_quote(*ptr, &quote);
		if (!quote && condition(ptr))
			return (ptr);
		ptr++;
	}
	return (NULL);
}

char	*ft_strnotset(char *str, char *set)
{
	int		i;
	int		y;

	while (str && set)
	{
		i = 0;
		y = 0;
		while (set[i] == *str)
			if (*str == set[i++])
				y = 1;
		if (!y)
			return (str);
		str++;
	}
	return (str);
}

char	**special_redirection(char **element, char *str)
{
	char	**tmp;
	int		i;

	tmp = ft_split_arg(str);
	if (!tmp)
		return (element);
	i = 1;
	element[2] = tmp[0];
	while (tmp[0] && tmp[i])
		free(tmp[i++]);
	free(tmp);
	if (!element[2])
		return (element);
	element[0] = ft_substr(str, ft_strlen(element[2]) + (ft_strlen(str) - \
		ft_strlen(ft_strnotset(str, SET_SPACE))), ft_strlen(str));
	return (element);
}
