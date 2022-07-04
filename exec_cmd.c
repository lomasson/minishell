/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasson <lomasson@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 10:02:20 by lomasson          #+#    #+#             */
/*   Updated: 2022/07/04 23:25:19 by lomasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* cmd in first args = command + arguments (-a)
, fd_in is the input and fd_out is the output.
exec_cmd take the input for execut the command and 
redirect to output*/
void	exec_cmd(char *command, int fd_in, int fd_out, char **env)
{
	int		pid;
	char	**cmd;
	char	*path;

	pid = fork();
	if (!pid)
	{
		cmd = ft_split(command, ' ');
		path = parsing_core(cmd[0], env);
		if (!path)
			return ;
		dup2(fd_in, STDIN_FILENO);
		dup2(fd_out, STDOUT_FILENO);
		if (fd_in != 0)
			close(fd_in);
		if (fd_out != 1)
			close(fd_out);
		if (ft_is_built_in(cmd[0]))
			ft_exec_built_in(cmd);
		else
		{
			if (execve(cmd[0], cmd, NULL) == -1)
				perror("shell");
			close(fd_in);
			close(fd_out);
			return ;
		}
	}
	else
	{
		waitpid(pid, NULL, 0);
	}
}

// fd[1] = out
// fd[0] = in

t_binbash	*exec_all_command(t_binbash *root, char **env)
{
	int		fd[2];
	int		fd_entry;
	int		out_gestion;
	char	**state;

	out_gestion = 0;
	state = (char **)root->content;
	fd_entry = STDIN_FILENO;
	while (state)
	{
		if (ft_strcmp(state[0], "<") == 0)
		{
			root = root->right;
			fd_entry = open(root->content, O_RDONLY);
			root = root->right;
		}
		else if (ft_strcmp(state[0], ">") == 0)
		{
			out_gestion = 1;
			fd[1] = open(*(char **) root->right->content,
					O_RDWR | O_CREAT | O_TRUNC, 0777);
		}
		else if (ft_strcmp(state[0], "|") == 0)
		{
			out_gestion = 2;
			pipe(fd);
		}
		else if (ft_strcmp(state[0], "||") == 0)
		{
			out_gestion = 2;
			pipe(fd);
		}
		else if (ft_strcmp(state[0], "&&") == 0)
		{
			out_gestion = 2;
			pipe(fd);
		}
		else if (ft_strcmp(state[0], ">>") == 0)
		{
			out_gestion = 1;
			fd[1] = open(*(char **)root->right->content,
					O_CREAT | O_APPEND, 0777);
		}
		else if (ft_strcmp(state[0], "<<") == 0)
		{
			out_gestion = 2;
			pipe(fd);
		}
		if (ft_is_built_in(state[0]) == 1)
			ft_exec_built_in(ft_split(state[0], ' '));
		else
			exec_cmd(root->content, fd_entry, fd[1], env);
		if (out_gestion == 2)
			fd_entry = fd[0];
		state = NULL;
	}
	return (root);
}
