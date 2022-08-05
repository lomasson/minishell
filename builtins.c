/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasson <lomasson@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 10:51:20 by lomasson          #+#    #+#             */
/*   Updated: 2022/08/05 12:57:19 by lomasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*execut the built-in informed in param*/
void	ft_exec_built_in(char **cmd_splited, t_exec_gestion *exec, t_environement *env, t_binbash *root)
{
	if (exec->fd_entry != 0)
	{
		dup2(exec->fd_entry, STDIN_FILENO);
		close(exec->fd_entry);
	}
	if (ft_strcmp(cmd_splited[0], "pwd") == 0)
		built_in_pwd(exec->fd[1]);
	else if (ft_strcmp(cmd_splited[0], "echo") == 0)
		built_in_echo(cmd_splited, exec->fd[1]);
	else if (ft_strcmp(cmd_splited[0], "env") == 0)
		built_in_env(env, exec->fd[1]);
	if (ft_strcmp(cmd_splited[0], "cd") == 0)
		built_in_cd(cmd_splited[1], env);
	else if (ft_strcmp(cmd_splited[0], "export") == 0)
		built_in_export(env, cmd_splited[1]);
	else if (ft_strcmp(cmd_splited[0], "unset") == 0)
		built_in_unset(env, cmd_splited[1]);
	else if (ft_strcmp(cmd_splited[0], "exit") == 0)
		ft_exit(cmd_splited, env, root, exec);
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
	if (ft_strcmp(command, "exit") == 0)
		return (true);
	return (false);
}

char	*change_old_path(t_environement *env)
{
	int		i;
	int		j;
	char	*str;

	j = 0;
	i = 0;
	while (ft_strncmp(env->var[i], "PWD", 3) != 0 && env->var[i])
			i++;
	while (ft_strncmp(env->var[j], "OLDPWD", 6) != 0 && env->var[j])
			j++;
	if (!env->var[i])
		return(env->var[j]);
	str = ft_strchr(env->var[i], '/');
	return (ft_strjoin("OLDPWD=", str));
}

void	built_in_export(t_environement *env, char *name)
{
	int				i;
	int				j;
	int				egal;
	int				egal_w;
	t_environement	*new;
	char			**dest;

	j = -1;
	i = -1;
	egal = 0;
	new = malloc(sizeof(t_environement));
	while (name[egal] != '=')
		egal++;
	egal_w = 0;
	while (name[egal_w] != '=')
		egal_w++;
	if (egal_w > egal)
		egal = egal_w;
	while (env->var && env->var[++i])
		if (ft_strncmp(env->var[i], name, egal + 1) == 0)
			j = i;
	dest = (char **)malloc(sizeof(char **) * ++i);
	if (j >= 0)
		ft_export_utils(env, env->var[j]);
	i = -1;
	while (env->var[++i])
		dest[i] = env->var[i];
	dest[i++] = name;
	dest[i] = NULL;
	env->var = dest;
}

void	built_in_unset(t_environement *env, char *name)
{
	int		i;

	i = -1;
	while (env->var[++i])
		if (ft_strncmp(env->var[i], name, ft_strlen(name)) == 0)
			break ;
	while (env->var[i])
	{
		env->var[i] = env->var[i + 1];
		i++;
	}
}

int	ft_export_utils(t_environement *env, char *name)
{
	int	i;
	int	j;
	int n;

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

int	ft_exit(char **state_tab, t_environement *env,
	t_binbash *root, t_exec_gestion *exec)
{
	int	i;
	int	j;

	i = 0;
	while (state_tab[++i])
	{
		if (i > 2)
		{
			ft_printf("exit: too many arguments\n");
			env->last = 1;
			return (1);
		}
	}
	i = 0;
	while (state_tab[++i])
	{
		j = -1;
		while (state_tab[i][++j])
		{
			if (!((state_tab[i][j] <= '9' && state_tab[i][j] >= '0')
				|| state_tab[i][j] >= ' '))
			{
				ft_printf("exit: %s: numeric argument required\n", state_tab[i]);
				env->last = 255;
				return (1);
			}
		}
	}
	//free(exec->state_tab);
	//del_arbre_binaire(root);
	//free(env->var);
	if (i > 1)
		env->last = ft_atoi(state_tab[1]);
	(void)root;
	(void)exec;
	exit(env->last);
}
