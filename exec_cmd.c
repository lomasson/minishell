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
void	exec_cmd(char **cmd, int fd_in, int fd_out, t_environement *env)
{
	int		pid;
	char	*path;

	pid = fork();
	if (!pid)
	{
		path = parsing_core(cmd[0], env->var);
		if (!path)
			return ;
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
			perror("shell");
		close(fd_in);
		close(fd_out);
		exit(EXIT_FAILURE);
	}
	else
		waitpid(pid, NULL, 0);
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
	int		pipe_e[2];
	int		parent;

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
			fd[0] = fd_entry;
			state_tab = (char **)root->left->content;
			out_gestion = 2;
			pipe (pipe_e);
			parent = fork();
			if (!parent)
			{
				if (state_tab[1])
					state_tab[0] = ft_strjoin(
							ft_strjoin(state_tab[0], " "), state_tab[1]);
				child_procces(fd[0], pipe_e, state_tab[0],
					parsing_core(state_tab[0], env->var));
				ft_putstr_fd("je passe ici\n", STDERR_FILENO);
				exit(EXIT_FAILURE);
			}
			else
				waitpid(parent, NULL, 0);
			close(pipe_e[1]);
			//close(pipe_e[0]);
			//close(fd[1]);
			root = root->right;
			if (root->type == 0)
				state_tab = (char **)root->content;
			else
			{
				state_tab[0] = (char *)root->content;
				state_tab[1] = NULL;
			}
			fd_entry = pipe_e[0];
		}
		else if (ft_strcmp(state_tab[0], "||") == 0)
			ft_printf("not work\n");
		else if (ft_strcmp(state_tab[0], "&&") == 0)
			ft_printf("not work\n");
		else if (ft_strcmp(state_tab[0], "<") == 0)
		{
			out_gestion = 1;
			if (root->right->type == 0)
				state_tmp = (char **)root->right->content;
			else
				state_tmp = (char **)root->right->left->content;
			fd_entry = open(state_tmp[0], O_RDWR);
			state_tmp = (char **)root->left->content;
			state_tab[0] = state_tmp[0];
		}
		else if (ft_strcmp(state_tab[0], ">") == 0)
		{
			out_gestion = 1;
			if (root->right->type == 0)
				state_tmp = (char **)root->right->content;
			else
				state_tmp = (char **)root->right->left->content;
			fd[1] = open(state_tmp[0],
					O_RDWR | O_CREAT | O_TRUNC, 0777);
				state_tmp = (char **)root->left->content;
			state_tab = state_tmp;
		}
		else if (ft_strcmp(state_tab[0], ">>") == 0)
		{
			out_gestion = 1;
			fd[1] = open(*(char **)root->right->content,
					O_CREAT | O_APPEND, 0777);
		}
		else if (ft_strcmp(state_tab[0], "<<") == 0)
			ft_printf("not work\n");
		if (out_gestion != 1)
			fd[1] = STDOUT_FILENO;
		if (ft_is_built_in(state_tab[0]))
			ft_exec_built_in(state_tab, fd_entry, fd, env);
		else if (state_tab && out_gestion != 2 )
			exec_cmd(state_tab, fd_entry, fd[1], env);
		if (out_gestion == 2)
			fd_entry = fd[0];
		if (!root->right && !root->left)
			break ;
		if (root->right)
			root = root->right;
		if (root->type == 0)
			state_tab = (char **)root->content;
		else
		{
			state_tab[0] = (char *)root->content;
			state_tab[1] = NULL;
		}
		out_gestion = 0;
	}
	return (root);
}
