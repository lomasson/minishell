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
		printf("address: %s\n", path);
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
		return ;
	}
	else
	{
		waitpid(pid, NULL, 0);
	}
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
	fd_entry = STDIN_FILENO;
	while (state_tab[0])
	{
		if (ft_strcmp(state_tab[0], "<") == 0)
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
		else if (ft_strcmp(state_tab[0], "|") == 0)
		{
			out_gestion = 2;
			pipe(fd);
		}
		else if (ft_strcmp(state_tab[0], "||") == 0)
		{
			out_gestion = 2;
			pipe(fd);
		}
		else if (ft_strcmp(state_tab[0], "&&") == 0)
		{
			out_gestion = 2;
			pipe(fd);
			root = root->left;
		}
		else if (ft_strcmp(state_tab[0], ">>") == 0)
		{
			out_gestion = 1;
			fd[1] = open(*(char **)root->right->content,
					O_CREAT | O_APPEND, 0777);
		}
		else if (ft_strcmp(state_tab[0], "<<") == 0)
		{
			out_gestion = 2;
			pipe(fd);
		}
		if (ft_is_built_in(state_tab[0]) == 1)
			ft_exec_built_in(state_tab, fd_entry, fd, env);
		else if (state_tab)
			exec_cmd(state_tab, fd_entry, fd[1], env);
		if (out_gestion == 2)
			fd_entry = fd[0];
		if (root->right)
			root = root->right;
		if (!root->right || !root->left)
			break ;
		break ;
		if (root->type == 1)
			state_tab = (char **)root->content;
		else
		{
			state_tab[0] = (char *)root->content;
		}
	}
	return (root);
}
