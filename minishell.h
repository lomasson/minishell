/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasson <lomasson@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 11:20:13 by lomasson          #+#    #+#             */
/*   Updated: 2022/08/02 16:05:27 by lomasson         ###   ########.fr       */
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
# include <sys/ioctl.h>
# include <curses.h>
# include <term.h>

# define SET_SPACE " \n\t\v\r\f"

typedef struct s_binbash
{
	int					type;
	char				*content;
	struct s_binbash	*right;
	struct s_binbash	*left;
	struct s_binbash	*prev;
}	t_binbash;

typedef struct s_environement
{
	char			**var;
	unsigned char	last;
}	t_environement;

typedef struct s_exec_gestion
{
	char	**state_tab;
	int		fd[2];
	int		fd_entry;
	int		out_gestion;
}	t_exec_gestion;

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
int			globale_verif(t_binbash *node, t_environement *env);
char		*ft_strjoin_get(char *s1, char *s2);
char		*parse_iter(char *str, int *quote, t_environement *env);
int			parse_argument(t_binbash *node, t_environement *env);
int			exec_cmd(char **command, int fd_in,
				int fd_out, t_environement *env);
void		exec_all_command(t_binbash *root, t_environement *env);
char		*parsing_access_test(char **path, char **cmd_splited);

void		ft_exec_built_in(char **cmd_splited, t_exec_gestion *exec,
				t_environement *env, t_binbash *root);
bool		ft_is_built_in(char *command);
void		built_in_cd(char *path, t_environement *env);
void		built_in_pwd(int fd);
void		built_in_echo(char **message, int fd);
void		built_in_env(t_environement *env, int fd);
char		*ft_change_path(char *op_path, char *path);
char		*change_old_path(t_environement *env);
void		built_in_export(t_environement *env, char *name);
void		built_in_unset(t_environement *env, char *name);
void		ft_tabjoin(t_environement *env, char *src);
int			ft_pipe(t_binbash *root,
				t_environement *env, int *fd_in, int *fd_out);
void		ft_export_utils(t_environement *env, char *name);
int			gestion_pipe(t_binbash *root, t_environement *env, int fd_entry);
int			gestion_heredoc(char *arg_stop);
int			ft_exit(char **state_tab, t_environement *env,
				t_binbash *root, t_exec_gestion *exec);
char		**output_redirection(int *out_gestion, t_binbash *root,
				char **state_tab, int *fd_out);
void		ft_exec_all_command_part_two(t_exec_gestion *exec,
				t_environement *env, t_binbash *root);
void		exec_struct_initer(t_binbash *root, t_exec_gestion *exec);
void		ft_pipe_exec(t_exec_gestion *exec,
				t_environement *env, t_binbash *root);
char		**input_redirection(t_environement *env, t_binbash *root,
				char **state_tab, t_exec_gestion *exec);
int			ft_interation_gestion(t_exec_gestion *exec,
				t_environement *env, t_binbash *root);
void		ft_find_error_numbers(t_environement *env, int status);
void		ft_heredoc(t_binbash *root, t_exec_gestion *exec,
				t_environement *env);
void		freetab(char **str);
void		struct_destroyer(t_exec_gestion *exec);
#endif