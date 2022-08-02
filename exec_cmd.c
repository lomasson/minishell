/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasson <lomasson@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 16:30:40 by lomasson          #+#    #+#             */
/*   Updated: 2022/08/02 16:20:23 by lomasson         ###   ########.fr       */
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
		{
			perror (cmd[0]);
			strerror(errno);
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
	ft_find_error_numbers(env, status);
	return (1);
}

// exec.fd[1] = out
// exec.fd[0] = in

void	exec_all_command(t_binbash *root, t_environement *env)
{
	t_exec_gestion	exec;

	exec_struct_initer(root, &exec);
	while (exec.state_tab[0])
	{
		env->last = 0;
		ft_exec_all_command_part_two(&exec, env, root);
		if (exec.out_gestion != 1 && exec.out_gestion != 2)
			exec.fd[1] = STDOUT_FILENO;
		if (ft_interation_gestion(&exec, env, root) == 0)
			break ;
	}
}

void	ft_exec_all_command_part_two(t_exec_gestion *exec,
	t_environement *env, t_binbash *root)
{
	exec->out_gestion = 0;
	if (exec->state_tab[0] && ft_strcmp(exec->state_tab[0], "|") == 0)
	{
		ft_pipe_exec(exec, env, root);
	}
	else if (ft_strncmp(exec->state_tab[0], ">>", 2) == 0
			|| ft_strcmp(exec->state_tab[0], ">") == 0)
		exec->state_tab = output_redirection(&exec->out_gestion,
				root, exec->state_tab, &exec->fd[1]);
	else if (exec->state_tab &&
			(ft_strcmp(exec->state_tab[0], "<<") == 0
			|| ft_strcmp(exec->state_tab[0], "<")) == 0)
		exec->state_tab = input_redirection(env, root,
				exec->state_tab, exec);
}

void	exec_struct_initer(t_binbash *root, t_exec_gestion *exec)
{
	exec->state_tab = ft_calloc(sizeof(char **), 3);
	if (root->type == 0)
		exec->state_tab = (char **)root->content;
	else
	{
		exec->state_tab[0] = (char *)root->content;
		exec->state_tab[1] = NULL;
		exec->state_tab[2] = NULL;
	}
	exec->fd[1] = 1;
	exec->fd[0] = 0;
	exec->fd_entry = STDIN_FILENO;
}

void	ft_pipe_exec(t_exec_gestion *exec,
	t_environement *env, t_binbash *root)
{
	exec->fd_entry = gestion_pipe(root, env, exec->fd[0]);
	*root = *root->right;
	if (root->type == 0)
	{
		exec->out_gestion = 1;
		exec->state_tab = (char **)root->content;
	}
	else
	{
		exec->out_gestion = 2;
		exec->state_tab[0] = (char *)root->content;
		exec->state_tab[1] = NULL;
	}
}

void	freetab(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free (str[i]);
	//free(str);
}
