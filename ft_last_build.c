/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_last_build.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasson <lomasson@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 15:25:16 by lomasson          #+#    #+#             */
/*   Updated: 2022/08/08 15:29:29 by lomasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path_home(t_environement *env)
{
	int	i;

	i = 0;
	while (ft_strncmp(env->var[i], "HOME", 4) != 0 && env->var[i])
		i++;
	if (!env->var[i])
	{
		ft_putstr_fd("cd: HOME not set", 3);
		return (NULL);
	}
	return (ft_strchr(env->var[i], '/'));
}

void	change_path_and_old(char *path, t_environement *env)
{
	int			i;
	int			j;
	static int	old;
	char		*str;
	char		**op_path;

	i = 0;
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

int	ft_export_utils(t_environement *env, char *name)
{
	int	i;
	int	j;
	int	n;

	n = 0;
	while (name[n] != '=')
		n++;
	i = 0;
	while (env->var[i] && ft_strcmp(env->var[i], name) != 0)
		i++;
	j = i - 1;
	if (env->var[i])
		while (env->var[++j])
			env->var[j] = env->var[j + 1];
	env->var[j] = NULL;
	return (1);
}

int	ft_str_egal(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=')
		i++;
	return (i);
}
