/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasson <lomasson@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 16:38:41 by lomasson          #+#    #+#             */
/*   Updated: 2022/07/08 19:32:33 by lomasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_H
# define PIPE_H

# include "../minishell.h"
# include "../libft/libft.h"

int		processing(int *fds, char **argv, char **command);
void	child_procces(int file, int *pipe, char *cmd, char *path);
void	parent_procces(int *file, int *pipe, char *cmd, char **path);
char	*parsing_core(char *cmd, char **env);
char	*parsing_access_test(char **path, char **cmd_splited);
int		exit_error(char *message);
int		pipex(int *fds, char **argv, char **env);
#endif
