/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasson <lomasson@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 16:31:10 by lomasson          #+#    #+#             */
/*   Updated: 2022/08/09 12:22:50 by lomasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	gestion_pipe(t_binbash *root, t_environement *env, int fd_entry)
{
	int		pipe_e[2];
	int		parent;
	int		status;

	status = 0;
	pipe (pipe_e);
	parent = fork();
	if (!parent)
	{
		dup2(fd_entry, STDIN_FILENO);
		dup2(pipe_e[1], STDOUT_FILENO);
		close(pipe_e[0]);
		close(pipe_e[1]);
		exec_all_command(*root->left, env);
		close(fd_entry);
		close(pipe_e[0]);
		close(pipe_e[1]);
		exit(EXIT_FAILURE);
	}
	else
		waitpid(parent, &status, 0);
	close(pipe_e[1]);
	ft_find_error_numbers(env, status);
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
		if (ft_strncmp(str, arg_stop, ft_strlen(arg_stop)) == 0)
			break ;
		ft_putstr_fd(str, fd);
		ft_putchar_fd('\n', fd);
	}
	lseek(fd, 0, SEEK_SET);
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
	if (state_tab && ft_strncmp(state_tab[0], ">", 2) == 0)
		fd_out[0] = open(state_tmp[0],
				O_RDWR | O_CREAT | O_TRUNC, 0777);
	else if (ft_strcmp(state_tab[0], ">>") == 0)
		fd_out[0] = open(state_tmp[0],
				O_CREAT | O_APPEND | O_RDWR, 0777);
	out_gestion[0] = 1;
	return ((char **)root->left->content);
}

char	**input_redirection(t_environement *env, t_binbash *root,
			char **state_tab, t_exec_gestion *exec)
{
	exec->out_gestion = 1;
	if (ft_strcmp(state_tab[0], "<") == 0)
	{
		if (root->right->type == 0)
			state_tab = (char **)root->right->content;
		else
			state_tab = (char **)root->right->left->content;
		exec->fd_entry = open(state_tab[0], O_RDWR);
		state_tab = (char **)root->left->content;
	}
	if (ft_strcmp(state_tab[0], "<<") == 0)
		ft_heredoc(root, exec, env);
	(void)env;
	return (state_tab);
}

int	ft_interation_gestion(t_exec_gestion *exec,
	t_environement *env, t_binbash *root)
{
	if (ft_is_built_in(exec->state_tab[0]))
		ft_exec_built_in(exec->state_tab, exec, env, root);
	else if (exec->state_tab && exec->out_gestion != 2
		&& exec->out_gestion != 3)
	{
		exec_cmd(exec->state_tab, exec->fd_entry, exec->fd[1], env);
	}
	if (root->right && exec->out_gestion != 2)
		*root = *root->right;
	if (!root->right && !root->left)
		return (0);
	if (exec->out_gestion == 2)
		exec->fd[0] = exec->fd_entry;
	else
	{
		if (root->type == 0)
			exec->state_tab = (char **)root->content;
		else
		{
			exec->state_tab[0] = (char *)root->content;
			exec->state_tab[1] = NULL;
		}
	}
	return (1);
}
