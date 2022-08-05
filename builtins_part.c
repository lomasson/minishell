/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_part.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasson <lomasson@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 16:52:11 by lomasson          #+#    #+#             */
/*   Updated: 2022/08/04 14:56:33 by lomasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	built_in_cd(char *path, t_environement *env)
{
	int			i;
	int			j;
	static int	old;
	char		*str;
	char		**op_path;

	i = 0;
	if (!path)
	{
		while (ft_strncmp(env->var[i], "HOME", 4) != 0 && env->var[i])
			i++;
		if (!env->var[i])
		{
			ft_putstr_fd("cd: HOME not set", 3);
			return ;
		}
		path = ft_strchr(env->var[i], '/');
	}
	i = 0;
	if (path[0] != '/')
	{
		while (ft_strncmp(env->var[i], "PWD", 3) != 0)
			i++;
		if (old++ > 0 && ft_strncmp(env->var[i + 1], "OLDPWD", 6) == 0)
			env->var[i + 1] = change_old_path(env);
		str = env->var[i];
		op_path = ft_split(path, '/');
		j = -1;
		while (op_path[++j])
			str = ft_change_path(op_path[j], str);
		env->var[i] = str;
		i = -1;
		while (op_path[++i])
			free(op_path[i]);
		free(op_path);
	}
	if (chdir(path) == -1)
		perror(path);
}

void	built_in_pwd(int fd)
{
	char	pwd[PATH_MAX];

	if (getcwd(pwd, sizeof(pwd)) == NULL)
		perror("getcwd()");
	else
	{
		ft_putstr_fd(pwd, fd);
		ft_putchar_fd('\n', fd);
	}
}

void	built_in_echo(char **message, int fd)
{
	int	i;

	i = 1;
	if (message[1])
		if (ft_strcmp(message[1], "-n") == 0)
			i++;
	while (message[i])
	{
		ft_putstr_fd(message[i++], fd);
		ft_putchar_fd(' ', fd);
	}
	if (message[1])
	{
		if (ft_strcmp(message[1], "-n") != 0)
			ft_putchar_fd('\n', fd);
	}
	else
		ft_putchar_fd('\n', fd);
}

void	built_in_env(t_environement *env, int fd)
{
	int	i;

	i = 0;
	while (env->var[i])
	{
		ft_putstr_fd(env->var[i++], fd);
		ft_putchar_fd('\n', fd);
	}
}

char	*ft_change_path(char *op_path, char *path)
{
	int		i;
	int		j;
	char	*str;

	i = -1;
	j = 0;
	if (ft_strcmp(op_path, "..") == 0)
	{
		while (path[++i])
			if (path[i] == '/')
				j = i;
		i = -1;
		str = malloc(sizeof(char) * ++j);
		ft_strlcpy(str, path, j);
	}
	else
		str = ft_strjoin(path, ft_strjoin("/", op_path));
	return (str);
}
