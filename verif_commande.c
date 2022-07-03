/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_commande.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajjar <chajjar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 14:50:51 by chajjar           #+#    #+#             */
/*   Updated: 2022/07/03 16:02:20 by chajjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//int	parse_argument(t_binbash *node)


int	globale_verif(t_binbash *node)
{
	if (!node)
		return (1);
	if (node->type && ((node->left && !node->left->type \
		&& (!node->left->content || !*((char **) node->left->content))) \
		|| (node->right && !node->right->type \
		&& (!node->right->content || !*(char **) node->right->content))))
		return (0);
	if (!globale_verif(node->left) || !globale_verif(node->right))
		return (0);
	return (1);
}
