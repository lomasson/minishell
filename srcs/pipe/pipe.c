/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasson <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 16:11:07 by lomasson          #+#    #+#             */
/*   Updated: 2022/06/28 12:39:37 by lomasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

int	processing(char **argv, char **command)
{
	int		pipe_e[2];
	int		parent;
	int		file_fd[2];

	file_fd[0] = open(argv[1], O_RDONLY);
	file_fd[1] = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0777);
	pipe (pipe_e);
	parent = fork();
	if (!parent)
	{
		close(file_fd[1]);
		child_procces(file_fd[0], pipe_e, argv[2], command);
	}
	else
	{
		parent_procces(file_fd, pipe_e, argv[3], command);
		waitpid(parent, NULL, 0);
	}
	return (1);
}

/* pipe need argc, argv and variable env return -1 if fail*/
int	pipex(int argc, char **argv, char **env)
{
	char	*command[2];

	if (argc != 5 || !argv[1][0] || !argv[2][0] || !argv[3][0] || !argv[4][0])
		return (exit_error(ft_strjoin("At least one argument is empty", "")));
	if (open(argv[1], O_RDONLY) == -1
		|| open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0777) == -1)
		return (exit_error(ft_strjoin(strerror(errno), "")));
	command[0] = parsing_core(argv[2], env);
	if (!command[0])
	{
		ft_putstr_fd("command not found: ", STDERR_FILENO);
		ft_putstr_fd(argv[2], STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
	}
	command[1] = parsing_core(argv[3], env);
	if (!command[1])
	{
		free (command[1]);
		free (command[0]);
		return (exit_error(ft_strjoin("command not found: ", argv[3])));
	}
	return (processing(argv, command));
}

void	child_procces(int file, int *pipe, char *cmd, char **path)
{
	char	**arg;
	int		i;

	arg = ft_split(cmd, ' ');
	dup2(file, STDIN_FILENO);
	dup2(pipe[1], STDOUT_FILENO);
	close(pipe[0]);
	close(pipe[1]);
	close(file);
	if (path[0])
		execve(path[0], arg, NULL);
	close(pipe[0]);
	close(pipe[1]);
	close(file);
	i = 0;
	while (arg[i])
		free(arg[i++]);
	free(arg);
	free(path[0]);
	free(path[1]);
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
	free(path[0]);
	free(path[1]);
}
