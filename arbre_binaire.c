/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arbre_binaire.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajjar <chajjar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 15:42:47 by chajjar           #+#    #+#             */
/*   Updated: 2022/07/02 17:45:30 by chajjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_binbash	*creat_node(void *content, t_binbash *prev)
{
	t_binbash	*node;

	node = (t_binbash *)malloc(sizeof(t_binbash));
	node->content = content;
	node->prev = prev;
	node->right = NULL;
	node->left = NULL;
	return (node);
}

int	main(int argc, char **argv)
{
	char	**test;

	if (argc < 2)
		return (1);
	test = ft_split_commande(argv[1], check_condition);
	if (!test || !test[1])
		test = ft_split_commande(argv[1], check_pipe);
	if (!test || !test[1])
		test = ft_split_commande(argv[1], check_redirection);
	for (int i = 0; test[i]; i++) {
		char **res = ft_split_arg(test[i]);
		for (int y = 0; res[y]; y++)
			ft_printf("[%d:%d] %s\n", i, y, res[y]);
	}
}
