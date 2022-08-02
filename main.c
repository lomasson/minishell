/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasson <lomasson@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 13:43:14 by chajjar           #+#    #+#             */
/*   Updated: 2022/08/02 10:18:11 by lomasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sigint_handler(int signal)
{
	if (signal == SIGINT)
	{

		
		//ft_putstr_fd("\033[13C\033[J\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}

}

int	main(int argc, char **argv, char **envp)
{
	t_binbash		*root;
	char			*buffer;
	t_environement	env;

	env.var = envp;
	env.last = 0;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		buffer = readline("\033[32mMINISHELL $> \033[0m");
		if (!buffer)
			return (0);
		add_history(buffer);
		root = arbre_decison_tree(creat_node(buffer, 0));
		//display_tree(root, 0);
		if (globale_verif(root, &env))
			exec_all_command(*root, &env);
		else
			ft_printf("parsing error retry\n");
		del_arbre_binaire(root);
	}
	(void)argc;
	(void)argv;
}
