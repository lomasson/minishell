/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasson <lomasson@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 21:53:45 by lomasson          #+#    #+#             */
/*   Updated: 2022/07/07 15:34:53 by lomasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_define_env_var(t_environement *env, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	env->var = (char **)malloc(sizeof(char) * (i + 1));
	i = -1;
	while (envp[++i])
		env->var[i] = envp[i];
	env->var[i] = NULL;
}
