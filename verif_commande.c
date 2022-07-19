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

static char	*find_var(char **env, char *key)
{
	char	*found;
	char	*search;
	size_t	i;
	size_t	y;

	y = 0;
	i = 0;
	found = NULL;
	while (key && ft_isalnum(key[y]))
		y++;
	if (y)
		search = ft_substr(key, 0, y);
	while (y && !found && env[i])
		found = ft_strnstr(env[i++], search, y);
	if (!found)
		return (ft_strdup(""));
	return (ft_substr(found, y + 2, ft_strlen(found) - y));
}

static char *parse_env(char *ptr, char *str, int *i, t_env *env)
{
	if (str[*i + 1] && str[*i + 1] == '?')
	{
		ptr = ft_strjoin_get(ptr, ft_itoa(env->last));
		(*i) += 2;
	}
	else
	{
		ptr = ft_strjoin_get(ptr, find_var(env->var, &str[++(*i)]));
		while (str[*i] && ft_isalnum(str[*i]))
			(*i)++;
	}
	return (ptr);
}

char	*parse_iter(char *str, int *quote, t_env *env)
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
			ptr = parse_env(ptr, &str[len], &i, env);
		if (str[len + i] == '\'' || str[len + i] == '\"' || str[len + i] == '$')
			len++;
		i += len;
	}
	return (ptr);
}

int	parse_argument(t_binbash *node, t_env *env)
{
	char	**str;
	int		quote;
	int		i;

	quote = 0;
	i = 0;
	str = (char **)node->content;
	while (str[i])
	{
		str[i] = parse_iter(str[i], &quote, env);
		node->content = (void *) str;
		if (quote != 0)
			return (1);
		i++;
	}
	return (0);
}

int	globale_verif(t_binbash *node, t_env *env)
{
	if (!node)
		return (1);
	if (node->type && ((node->left && !node->left->type \
		&& (!node->left->content || !*((char **) node->left->content))) \
		|| (node->right && !node->right->type \
		&& (!node->right->content || !*(char **) node->right->content))))
		return (0);
	if (!node->type && parse_argument(node, env))
		return (0);
	if (!globale_verif(node->left, env) || !globale_verif(node->right, env))
		return (0);
	return (1);
}
