/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_condition.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajjar <chajjar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 14:01:51 by chajjar           #+#    #+#             */
/*   Updated: 2022/07/02 15:37:24 by chajjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_condition(char *str)
{
	if (!str)
		return (0);
	else if (!ft_strncmp(str, "&&", 2) || !ft_strncmp(str, "||", 2))
		return (2);
	return (0);
}

int	check_pipe(char *str)
{
	if (!str)
		return (0);
	else if (!ft_strncmp(str, "|", 1))
		return (1);
	return (0);
}

int	check_redirection(char *str)
{
	if (!str)
		return (0);
	else if (!ft_strncmp(str, "<<", 2) || !ft_strncmp(str, ">>", 2))
		return (2);
	else if (!ft_strncmp(str, "<", 1) || !ft_strncmp(str, ">", 1))
		return (1);
	return (0);
}

void	check_quote(char c, int *quote)
{
	if (c == '\'' && *quote == 1)
		*quote = 0;
	else if (c == '\'' && *quote == 0)
		*quote = 1;
	else if (c == '\"' && *quote == 2)
		*quote = 0;
	else if (c == '\"' && *quote == 0)
		*quote = 2;
}
