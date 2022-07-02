/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajjar <chajjar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 16:38:41 by lomasson          #+#    #+#             */
/*   Updated: 2022/07/02 16:04:05 by chajjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_H
# define PIPE_H

# include "../minishell.h"
# include "../libft/libft.h"

int		processing(char **argv, char **command);
void	child_procces(int file, int *pipe, char *cmd, char **path);
void	parent_procces(int *file, int *pipe, char *cmd, char **path);
char	*parsing_core(char *cmd, char **env);
char	*parsing_access_test(char **path, char **cmd_splited);
int		exit_error(char *message);
int		pipex(int argc, char **argv, char **env);
#endif
