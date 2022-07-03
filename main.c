/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajjar <chajjar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 13:43:14 by chajjar           #+#    #+#             */
/*   Updated: 2022/07/03 13:43:30 by chajjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv)
{
	t_binbash	*root;

	if (argc < 2)
		return (1);
	root = arbre_decison_tree(creat_node(argv[1], 0));
	display_tree(root, 0);
}