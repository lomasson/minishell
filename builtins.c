/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasson <lomasson@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 10:51:20 by lomasson          #+#    #+#             */
/*   Updated: 2022/07/04 18:15:21 by lomasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*execut the built-in informed in param*/
void	ft_exec_built_in(char **cmd_splited)
{
	ft_printf("%s\n", cmd_splited[0]);
	if (ft_strcmp(cmd_splited[0], "pwd") == 0)
		built_in_pwd();
	else if (ft_strcmp(cmd_splited[0], "cd") == 0)
		built_in_cd(cmd_splited[1]);
}

/* Check if command informed in param is a built-in*/
bool	ft_is_built_in(char *command)
{
	if (ft_strcmp(command, "echo") == 0)
		return (false);
	if (ft_strcmp(command, "echo -n") == 0)
		return (false);
	if (ft_strcmp(command, "cd") == 0)
		return (true);
	if (ft_strcmp(command, "pwd") == 0)
		return (true);
	if (ft_strcmp(command, "export") == 0)
		return (false);
	if (ft_strcmp(command, "unset") == 0)
		return (false);
	if (ft_strcmp(command, "env") == 0)
		return (false);
	return (NULL);
}

void	built_in_cd(char *path)
{
	if (chdir(path) == -1)
		perror("chdir()");
}

void	built_in_pwd(void)
{
	char	pwd[PATH_MAX];

	ft_printf("%s\n", "hello");
	if (getcwd(pwd, sizeof(pwd)) == NULL)
		perror("getcwd()");
	else
		ft_printf("%s\n", pwd);
}
