/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasson <lomasson@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 10:51:20 by lomasson          #+#    #+#             */
/*   Updated: 2022/07/06 20:38:23 by lomasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*execut the built-in informed in param*/
void	ft_exec_built_in(char **cmd_splited,
	int fd_entry, int *fds, t_environement *env)
{
	if (fd_entry != 0)
	{
		dup2(fd_entry, STDIN_FILENO);
		close(fd_entry);
	}
	if (ft_strcmp(cmd_splited[0], "pwd") == 0)
		built_in_pwd(fds[1]);
	else if (ft_strcmp(cmd_splited[0], "echo") == 0)
		built_in_echo(cmd_splited, fds[1]);
	else if (ft_strcmp(cmd_splited[0], "env") == 0)
		built_in_env(env, fds[1]);
	if (ft_strcmp(cmd_splited[0], "cd") == 0)
		built_in_cd(cmd_splited[1], env);
	else if (ft_strcmp(cmd_splited[0], "export") == 0)
		built_in_export(env, cmd_splited[1]);
	else if (ft_strcmp(cmd_splited[0], "unset") == 0)
		built_in_unset(env, cmd_splited[1]);
}

/* Check if command informed in param is a built-in*/
bool	ft_is_built_in(char *command)
{
	if (ft_strcmp(command, "echo") == 0)
		return (true);
	if (ft_strcmp(command, "echo -n") == 0)
		return (true);
	if (ft_strncmp(command, "cd", 2) == 0)
		return (true);
	if (ft_strcmp(command, "pwd") == 0)
		return (true);
	if (ft_strcmp(command, "export") == 0)
		return (true);
	if (ft_strcmp(command, "unset") == 0)
		return (true);
	if (ft_strcmp(command, "env") == 0)
		return (true);
	return (NULL);
}

char	*change_old_path(t_environement *env)
{
	int		i;
	int		j;
	char	*str;

	j = 0;
	i = 0;
	while (ft_strncmp(env->var[i], "PWD", 3) != 0)
			i++;
	while (ft_strncmp(env->var[j], "OLDPWD", 6) != 0)
			j++;
	str = ft_strchr(env->var[i], '/');
	return (ft_strjoin("OLDPWD=", str));
	ft_printf("old: %s\n", env->var[j]);
	free (str);
}

void	built_in_export(t_environement *env, char *name)
{
	int	pos;
	int	i;
	int	j;
	//char *str;

	pos = 0;
	i = 0;
	j = -1;
	while (env->var[pos])
		pos++;
	/*while (name[i] != '=')
		i++;
	if (i == 0)
		return ;
	str = malloc(sizeof(char) * i);
	while (++j < i)
		str[j] = name[j];*/
	env->var[pos] = name;
	ft_printf("je passe ici: %s\n", env->var[pos]);
}

void	built_in_unset(t_environement *env, char *name)
{
	int	i;

	i = 0;
	while (ft_strncmp(env->var[i], name, ft_strlen(name)) != 0 || env->var[i])
		i++;
	env->var[i] = NULL;
}
