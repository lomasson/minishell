/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasson <lomasson@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 13:43:14 by chajjar           #+#    #+#             */
/*   Updated: 2022/07/04 23:25:09 by lomasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_binbash	*root;
	char		*buffer;

	(void)argc;
	(void)argv;
	while (1)
	{
		buffer = readline("\033[32mMINISHELL $> \033[0m");
		if (!buffer)
			return (0);
		root = arbre_decison_tree(creat_node(buffer, 0));
		if (globale_verif(root))
			display_tree(root, 0);
		else
			ft_printf("parsing error retry\n");
		root = exec_all_command(root, env);
		del_arbre_binaire(root);
	}
}
