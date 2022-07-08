/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasson <lomasson@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 16:11:07 by lomasson          #+#    #+#             */
/*   Updated: 2022/07/08 19:32:29 by lomasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

int	processing(int *fds, char **argv, char **command)
{
	int		pipe_e[2];
	int		parent;

	pipe (pipe_e);
	parent = fork();
	if (!parent)
	{
		close(fds[1]);
		child_procces(fds[0], pipe_e, argv[0], command[0]);
	}
	else
	{
		parent_procces(fds, pipe_e, argv[1], command);
		waitpid(parent, NULL, 0);
	}
	return (1);
}

int	pipex(int *fds, char **argv, char **env)
{
	char	*command[2];

	command[0] = parsing_core(argv[0], env);
	if (!command[0])
	{
		ft_putstr_fd("command not found: ", STDERR_FILENO);
		ft_putstr_fd(argv[0], STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
	}
	command[1] = parsing_core(argv[1], env);
	if (!command[1])
	{
		free (command[1]);
		free (command[0]);
		return (exit_error(ft_strjoin("command not found: ", argv[1])));
	}
	return (processing(fds, argv, command));
}

void	child_procces(int file, int *pipe, char *cmd, char *path)
{
	char	**arg;
	int		i;

	arg = ft_split(cmd, ' ');
	dup2(file, STDIN_FILENO);
	dup2(pipe[1], STDOUT_FILENO);
	close(pipe[0]);
	close(pipe[1]);
	close(file);
	if (path)
		execve(path, arg, NULL);
	close(pipe[0]);
	close(pipe[1]);
	close(file);
	i = 0;
	while (arg[i])
		free(arg[i++]);
	free(arg);
	free(path);
}

void	parent_procces(int *file, int *pipe, char *cmd, char **path)
{
	char	**arg;
	int		i;

	arg = ft_split(cmd, ' ');
	dup2(pipe[0], STDIN_FILENO);
	dup2(file[1], STDOUT_FILENO);
	close(pipe[0]);
	close(pipe[1]);
	close(file[1]);
	close(file[0]);
	if (path[1])
		execve(path[1], arg, NULL);
	close(pipe[0]);
	close(pipe[1]);
	close(file[1]);
	close(file[0]);
	i = 0;
	while (arg[i])
		free(arg[i++]);
	free(arg);
	free(path);
}
