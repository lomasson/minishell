/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasson <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 16:33:32 by lomasson          #+#    #+#             */
/*   Updated: 2022/06/28 12:25:51 by lomasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

char	*parsing_access_test(char **path, char **cmd_splited)
{
	char	*test;
	char	*command;
	int		i;

	i = -1;
	while (path[++i])
	{
		test = ft_strjoin(path[i], "/");
		command = ft_strjoin(test, cmd_splited[0]);
		free (test);
		if (access(command, R_OK) == 0)
			return (command);
		free (command);
	}
	return (NULL);
}

char	*parsing_core(char *cmd, char **env)
{
	char	**path;
	char	*command;
	char	**cmd_splited;
	int		j;
	int		i;

	cmd_splited = ft_split(cmd, ' ');
	i = 0;
	while (ft_strncmp(env[i], "PATH", 4))
		i++;
	path = ft_split(env[i], ':');
	j = -1;
	command = parsing_access_test(path, cmd_splited);
	i = -1;
	while (path[++i])
		free (path[i]);
	free (path);
	while (cmd_splited[++j])
		free (cmd_splited[j]);
	free (cmd_splited);
	return (command);
}

int	exit_error(char *message)
{
	ft_putstr_fd(message, STDERR_FILENO);
	free (message);
	write(STDERR_FILENO, "\n", 1);
	return (-1);
}
