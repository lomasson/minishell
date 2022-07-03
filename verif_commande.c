/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_commande.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajjar <chajjar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 14:50:51 by chajjar           #+#    #+#             */
/*   Updated: 2022/07/03 22:37:50 by chajjar          ###   ########.fr       */
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

//replace variable d'env avec placeholder pour $
char	*parse_iter(char *str, int *quote)
{
	char	*ptr;
	int		len;
	int		i;

	i = 0;
	ptr = (char *) ft_calloc(1, sizeof(char));
	while (str[i])
	{
		len = 0;
		while (str[len + i] && (*quote == 2 || str[len + i] != '\'')
			&& (*quote == 1 || (str[len + i] != '\"' && str[len + i] != '$')))
			len++;
		ptr = ft_strjoin_get(ptr, ft_substr(str, i, len));
		check_quote(str[len + i], quote);
		if (*quote != 1 && str[len + i] == '$')
			ptr = ft_strjoin_get(ptr, ft_strdup("%PLACEHOLDER%"));
		if (str[len + i] == '\'' || str[len + i] == '\"' || str[len + i] == '$')
			len++;
		i += len;
	}
	return (ptr);
}

int	parse_argument(t_binbash *node)
{
	char	**str;
	int		quote;
	int		i;

	quote = 0;
	i = 0;
	str = (char **)node->content;
	while (str[i])
	{
		str[i] = parse_iter(str[i], &quote);
		node->content = (void *) str;
		if (quote != 0)
			return (1);
		i++;
	}
	return (0);
}

int	globale_verif(t_binbash *node)
{
	if (!node)
		return (1);
	if (node->type && ((node->left && !node->left->type \
		&& (!node->left->content || !*((char **) node->left->content))) \
		|| (node->right && !node->right->type \
		&& (!node->right->content || !*(char **) node->right->content))))
		return (0);
	if (!node->type && parse_argument(node))
		return (0);
	if (!globale_verif(node->left) || !globale_verif(node->right))
		return (0);
	return (1);
}
