/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasson <lomasson@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 13:43:14 by chajjar           #+#    #+#             */
/*   Updated: 2022/08/09 13:12:41 by lomasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sigint_handler(int signal)
{
	if (signal == SIGINT)
	{
		ft_printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	free_array(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free (str[i]);
	free(str);
}

int	main(int argc, char **argv, char **envp)
{
	t_binbash		*root;
	char			*buffer;
	t_environement	env;

	env.var = ft_copy_env(envp);
	env.last = 0;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		buffer = readline("\033[32mMINISHELL $> \033[0m");
		if (!buffer)
			exit (1);
		add_history(buffer);
		root = arbre_decison_tree(creat_node(buffer, 0));
		if (globale_verif(root, &env))
			exec_all_command(*root, &env);
		else
			ft_printf("syntax error near\n");
		del_arbre_binaire(root);
	}
	(void)argc;
	(void)argv;
}
