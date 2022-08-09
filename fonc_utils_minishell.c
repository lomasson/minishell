/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonc_utils_minishell.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasson <lomasson@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 14:40:43 by lomasson          #+#    #+#             */
/*   Updated: 2022/08/09 11:48:33 by lomasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_split_commande(char *str, int (*condition)(char *))
{
	char	**element;

	element = ft_calloc(4, sizeof(char *));
	if (element)
		element = ft_alloc_element(element, str, condition);
	return (element);
}

char	**ft_alloc_element(
	char **element, char *str, int (*condition)(char *))
{
	size_t	len;
	size_t	len2;

	len2 = 0;
	if (occurent(str, condition))
		len2 = ft_strlen(occurent(str, condition));
	len = ft_strlen(str) - len2;
	if (ft_strnotset(str, SET_SPACE) != &str[len])
	{
		element[0] = ft_calloc(len + 1, sizeof(char));
		ft_strlcpy(element[0], str, len + 1);
	}
	if (condition(&str[len]))
	{
		element[1] = ft_calloc(condition(&str[len + 1]), sizeof(char));
		ft_strlcpy(element[1], &str[len], condition(&str[len]) + 1);
	}
	return (ft_alloc_ellement_two(element, str, condition, len2));
}

char	**ft_alloc_ellement_two(char **element, char *str,
	int (*condition)(char *), int len2)
{
	int	len;

	len = ft_strlen(str) - len2;
	if (len2 && ft_strnotset(str, SET_SPACE) == &str[len]
		&& (ft_strncmp(&str[len], "<", 1) || ft_strncmp(&str[len], ">", 1)))
		element = special_redirection(
				element, &str[len] + condition(&str[len]));
	else if (len2)
	{
		element[2] = ft_calloc(len2 + 1, sizeof(char));
		ft_strlcpy(element[2], &str[len + condition(&str[len])], len2 + 1);
	}
	return (element);
}

void	ft_child_fonc(char **cmd, int fd_in, int fd_out, t_environement *env)
{
	char	*path;

	path = cmd[0];
	if (parsing_core(cmd[0], env->var))
		path = parsing_core(cmd[0], env->var);
	if (fd_in != 0)
	{
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	if (fd_out != 1)
	{
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
	if (execve(path, cmd, env->var) == -1)
		if (path)
			env->last = error_message(path);
	close(fd_in);
	close(fd_out);
	free (path);
	exit(env->last);
}

int	ft_check_arg_exit(char **state_tab, t_environement *env)
{
	int	i;
	int	j;

	i = 0;
	while (state_tab[++i])
	{
		j = -1;
		while (state_tab[i][++j])
		{
			if (!(state_tab[i][j] <= '9' && state_tab[i][j] >= '0'))
			{
				ft_printf("exit: %s: numeric argument required\n", state_tab[i]);
				env->last = 255;
				return (-1);
			}
		}
	}
	return (i);
}
