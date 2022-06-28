/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasson <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 11:19:31 by lomasson          #+#    #+#             */
/*   Updated: 2022/06/28 12:54:26 by lomasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*brut_command;

	(void)argc;
	(void)argv;
	(void)env;
	while (1)
	{
		ft_printf("$> ");
		brut_command = get_next_line(STDIN_FILENO);
		ft_printf("%s", brut_command);
	}
}
