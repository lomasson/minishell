/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasson <lomasson@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 11:20:13 by lomasson          #+#    #+#             */
/*   Updated: 2022/07/04 18:06:56 by lomasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>
# include "libft/libft.h"
# include "pipex/pipe.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <stdbool.h>
# include <signal.h>

typedef struct s_binbash
{
	int					type;
	char				*content;
	struct s_binbash	*right;
	struct s_binbash	*left;
	struct s_binbash	*prev;
}	t_binbash;

int			check_condition(char *str);
int			check_pipe(char *str);
int			check_redirection(char *str);
void		check_quote(char c, int *quote);
char		**ft_split_at(char *str, int (*condition)(char *));
char		*occurent(char *str, int (*condition)(char *));
char		**ft_split_commande(char *str, int (*condition)(char *));
char		**ft_split_arg(char *str);
t_binbash	*creat_node(void *content, t_binbash *prev);
t_binbash	*arbre_decison_tree(t_binbash *node);
void		del_arbre_binaire(t_binbash *root);
void		display_args(char **args);
void		display_tree(t_binbash *node, int depth);
int			globale_verif(t_binbash *node);
char		*ft_strjoin_get(char *s1, char *s2);
char		*parse_iter(char *str, int *quote);
int			parse_argument(t_binbash *node);
void		exec_cmd(char *command, int fd_in, int fd_out, char **env);
t_binbash	*exec_all_command(t_binbash *root, char **env);
char		*parsing_access_test(char **path, char **cmd_splited);
void		ft_exec_built_in(char **cmd_splited);
bool		ft_is_built_in(char *command);
void		built_in_cd(char *path);
void		built_in_pwd(void);

#endif