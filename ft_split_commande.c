/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_commande.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajjar <chajjar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 13:49:03 by chajjar           #+#    #+#             */
/*   Updated: 2022/07/03 13:29:26 by chajjar          ###   ########.fr       */
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

static char	**ft_alloc_element(
	char **element, char *str, int (*condition)(char *))
{
	size_t	len;
	size_t	len2;

	len2 = 0;
	if (occurent(str, condition))
		len2 = ft_strlen(occurent(str, condition));
	len = ft_strlen(str) - len2;
	if (len)
	{
		element[0] = ft_calloc(len, sizeof(char));
		ft_strlcpy(element[0], str, len + 1);
	}
	if (condition(&str[len]))
	{
		element[1] = ft_calloc(condition(&str[len]), sizeof(char));
		ft_strlcpy(element[1], &str[len], condition(&str[len]) + 1);
	}
	if (len2)
	{
		element[2] = ft_calloc(len2, sizeof(char));
		ft_strlcpy(element[2], &str[len + condition(&str[len])], len2 + 1);
	}
	return (element);
}

char	**ft_split_commande(char *str, int (*condition)(char *))
{
	char	**element;

	element = ft_calloc(4, sizeof(char *));
	if (element)
		element = ft_alloc_element(element, str, condition);
	return (element);
}
