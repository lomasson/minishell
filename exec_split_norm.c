/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_split_norm.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasson <lomasson@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 14:15:41 by lomasson          #+#    #+#             */
/*   Updated: 2022/08/09 13:27:11 by lomasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_message(char *path)
{
	DIR	*folder;
	int	fd;
	int	ret;

	fd = open(path, O_WRONLY);
	folder = opendir(path);
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(path, STDERR_FILENO);
	if (ft_strchr(path, '/') == NULL)
		ft_putendl_fd(": command not found", STDERR_FILENO);
	else if (fd == -1 && folder == NULL)
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
	else if (fd == -1 && folder != NULL)
		ft_putendl_fd(": is a directory", STDERR_FILENO);
	else if (fd != -1 && folder == NULL)
		ft_putendl_fd(": Permission denied", STDERR_FILENO);
	if (ft_strchr(path, '/') == NULL || (fd == -1 && folder == NULL))
		ret = 127;
	else
		ret = 126;
	if (folder)
		closedir(folder);
	close(fd);
	return (ret);
}

char	**ft_copy_env(char **envp)
{
	int		i;
	char	**dest;

	i = 0;
	while (envp[i])
		i++;
	dest = (char **)malloc(sizeof(char *) * i);
	i = -1;
	while (envp[++i])
	{
		dest[i] = malloc(sizeof(char) * (ft_strlen(envp[i]) + 1));
		ft_strlcpy(dest[i], envp[i], ft_strlen(envp[i]) + 1);
	}
	dest[i] = NULL;
	return (dest);
}

void	ft_find_error_numbers(t_environement *env, int status)
{
	if (status == 32256 || status == 32512)
		env->last /= 256;
	else
		env->last = !!status;
}

void	ft_heredoc(t_binbash *root, t_exec_gestion *exec, t_environement *env)
{
	char	**state_tab;
	char	**state_tmp;

	state_tab = exec->state_tab;
	state_tmp = exec->state_tab;
	if (root->right->type == 0)
	{
		state_tab = (char **)root->right->content;
		exec->fd[1] = STDOUT_FILENO;
		pipe(exec->fd);
		exec->fd_entry = exec->fd[0];
	}
	else
		state_tab = def_state(state_tab, root, exec);
	state_tmp[0] = "cat";
	state_tmp[1] = "/tmp/heredoc";
	state_tmp[2] = NULL;
	exec->out_gestion = 3;
	gestion_heredoc(state_tab[0]);
	(void)env;
	if (*(char *)state_tmp[0] == *(char *)"cat")
		exec_cmd(state_tmp, STDIN_FILENO, exec->fd[1], env);
	*root = *root->right;
}

int	ft_exit(char **state_tab, t_environement *env,
	t_binbash *root, t_exec_gestion *exec)
{
	int	i;

	i = 0;
	while (state_tab[++i])
	{
		if (i > 2)
		{
			ft_printf("exit: too many arguments\n");
			env->last = 1;
			return (-1);
		}
	}
	i = ft_check_arg_exit(state_tab, env);
	if (i < 0)
		return (-1);
	if (i > 1)
		env->last = ft_atoi(state_tab[1]);
	(void)root;
	(void)exec;
	exit(env->last);
}
