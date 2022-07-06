/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasson <lomasson@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 13:43:14 by chajjar           #+#    #+#             */
/*   Updated: 2022/07/06 20:36:12 by lomasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_binbash		*root;
	char			*buffer;
	t_environement	env;
	int				i;

	i = 0;
	env.var = (char **)malloc(sizeof(char) * 1000);
	while (i <= 1000)
		env.var[i++] = NULL;
	env.var = envp;
	(void)argc;
	(void)argv;
	while (1)
	{
		buffer = readline("\033[32mMINISHELL $> \033[0m");
		if (!buffer)
			return (0);
		root = arbre_decison_tree(creat_node(buffer, 0));
		if (globale_verif(root))
			root = exec_all_command(root, &env);
		else
			ft_printf("parsing error retry\n");
		del_arbre_binaire(root);
	}
	(void)env;
}
