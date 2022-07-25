/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasson <lomasson@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 10:02:20 by lomasson          #+#    #+#             */
/*   Updated: 2022/07/05 14:01:49by lomasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* cmd in first args = command + arguments (-a)
, fd_in is the input and fd_out is the output.
exec_cmd take the input for execut the command and 
redirect to output*/
int	exec_cmd(char **cmd, int fd_in, int fd_out, t_environement *env)
{
	int		pid;
	char	*path;
	int		status;

	status = 0;
	pid = fork();
	if (!pid)
	{
		path = parsing_core(cmd[0], env->var);
		if (!path)
			exit (-1);
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
		if (execve(path, cmd, NULL) == -1)
		{
			close(fd_in);
			close(fd_out);
			exit(errno);
		}
		close(fd_in);
		close(fd_out);
		exit(EXIT_FAILURE);
	}
	else
		waitpid(pid, &status, 0);
	if (status == 32256 || status == 32512)
		env->last /= 256;
	else
		env->last = !!status;
	return (1);
}

// fd[1] = out
// fd[0] = in

t_binbash	*exec_all_command(t_binbash *root, t_environement *env)
{
	int		fd[2];
	int		fd_entry;
	int		out_gestion;
	char	**state_tab;
	char	**state_tmp;

	out_gestion = 0;
	if (root->type == 0)
		state_tab = (char **)root->content;
	else
	{
		state_tab = (char **)malloc(sizeof(char) * 2);
		state_tab[0] = (char *)root->content;
		state_tab[1] = NULL;
	}
	fd[1] = 1;
	fd[0] = 0;
	state_tmp = (char **)malloc(sizeof(char) * 2);
	state_tmp[0] = NULL;
	state_tmp[1] = NULL;
	fd_entry = STDIN_FILENO;
	while (state_tab[0])
	{
		if (ft_strcmp(state_tab[0], "|") == 0)
		{
			fd_entry = gestion_pipe(root, env, fd[0]);
			root = root->right;
			if (root->type == 0)
			{
				out_gestion = 1;
				state_tab = (char **)root->content;
			}
			else
			{
				out_gestion = 2;
				state_tab[0] = (char *)root->content;
				state_tab[1] = NULL;
			}
		}
		/*else if (ft_strcmp(state_tab[0], "||") == 0)
			ft_printf("not work\n");
		else if (ft_strcmp(state_tab[0], "&&") == 0)
			ft_printf("not work\n");*/
		else if (ft_strcmp(state_tab[0], "<") == 0)
		{
			out_gestion = 1;
			if (root->right->type == 0)
				state_tmp = (char **)root->right->content;
			else
				state_tmp = (char **)root->right->left->content;
			fd_entry = open(state_tmp[0], O_RDWR);
			state_tab = (char **)root->left->content;
		}
		else if (ft_strcmp(state_tab[0], ">>") == 0
			|| ft_strcmp(state_tab[0], ">") == 0)
			state_tab = output_redirection(&out_gestion,
					root, state_tab, &fd[1]);
		else if (ft_strcmp(state_tab[0], "<<") == 0)
		{
			out_gestion = 1;
			if (root->right->type == 0)
				state_tmp = (char **)root->right->content;
			else
				state_tmp = (char **)root->right->left->content;
			fd_entry = gestion_heredoc(state_tmp[0]);
			root = root->right;
		}
		if (out_gestion != 1)
			fd[1] = STDOUT_FILENO;
		if (ft_is_built_in(state_tab[0]))
			ft_exec_built_in(state_tab, fd_entry, fd, env);
		else if (state_tab && out_gestion != 2)
			exec_cmd(state_tab, fd_entry, fd[1], env);
		if (!root->right && !root->left)
			break ;
		if (out_gestion == 2)
			fd[0] = fd_entry;
		else
		{
			if (root->right)
				root = root->right;
			if (root->type == 0)
				state_tab = (char **)root->content;
			else
			{
				state_tab[0] = (char *)root->content;
				state_tab[1] = NULL;
			}
		}
		out_gestion = 0;
	}
	return (root);
}

int	gestion_pipe(t_binbash *root, t_environement *env, int fd_entry)
{
	int		pipe_e[2];
	int		parent;
	char	**state_tab;
	int		i;
	int		status;

	status = 0;
	pipe (pipe_e);
	parent = fork();
	if (!parent)
	{
		state_tab = (char **)root->left->content;
		if (state_tab[1])
			state_tab[0] = ft_strjoin(
					ft_strjoin(state_tab[0], " "), state_tab[1]);
		child_procces(fd_entry, pipe_e, state_tab[0],
			parsing_core(state_tab[0], env->var));
		i = -1;
		while (state_tab[++i])
			free (state_tab[i]);
		free (state_tab);
		exit(EXIT_FAILURE);
	}
	else
		waitpid(parent, NULL, 0);
	close(pipe_e[1]);
	if (status == 32256 || status == 32512)
		env->last /= 256;
	else
		env->last = !!status;
	return (pipe_e[0]);
}

int	gestion_heredoc(char *arg_stop)
{
	int		fd;
	char	*str;

	fd = open("/tmp/heredoc", O_CREAT | O_RDWR | O_TRUNC, 0666);
	while (1)
	{
		str = readline("\033[32mheredoc> \033[0m");
		if (ft_strcmp(str, arg_stop) == 0)
			break ;
		ft_putstr_fd(str, fd);
		ft_putchar_fd('\n', fd);
	}
	return (fd);
}

char	**output_redirection(int *out_gestion, t_binbash *root,
			char **state_tab, int *fd_out)
{
	char	**state_tmp;

	if (root->right->type == 0)
		state_tmp = (char **)root->right->content;
	else
		state_tmp = (char **)root->right->left->content;
	if (ft_strcmp(state_tab[0], ">") == 0)
		fd_out[0] = open(state_tmp[0],
				O_RDWR | O_CREAT | O_TRUNC, 0777);
	else if (ft_strcmp(state_tab[0], ">>") == 0)
		fd_out[0] = open(state_tmp[0],
				O_CREAT | O_APPEND | O_RDWR, 0777);
	out_gestion[0] = 1;
	return ((char **)root->left->content);
}
