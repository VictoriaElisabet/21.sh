/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <vgrankul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 10:24:05 by vgrankul          #+#    #+#             */
/*   Updated: 2020/02/27 13:01:07 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/types.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>
# include "./libft/libft.h"

# define BUF_SIZE 32

# define PIPE_OP		1
# define OR_OP			2
# define PIPE_AMP_OP	4
# define AMP_OP 		8
# define AND_OP 		16
# define S_COL_OP		32
# define NEWLINE		64

typedef struct	s_env
{
	char *name;
	char *value;

}				t_env;

typedef struct	s_command
{
	char		*command;
	char		**variables;
	char		**argv;
	int			argc;
	char		*ctrl_op;

}				t_command;

int				str_chr(char *str, int c);
int				ft_setenv(int argc, char *name, char *value, char ***env);
int				count_arr(char **arr);
int				ft_unsetenv(int argc, char **argv, char ***env);
int				ft_cd (int argc, char **argv, char ***env);
int				ft_echo(char **argv);
int				is_builtin(t_command *command);
int				run_builtin(t_command *command, char **command_list,
				char ***env, int status);
int				exec_command(t_command *commands, char **command_list,
				char ***env);
int				find_env(const char *name, char **env);
int				ft_env(t_command *command, char **env);
int				ft_exit(t_command *command, char**command_list, char ***env,
				int status);
int				handle_command_list(char **command_list, char ***env);
int				count_list(char **list);
int				print_exec_error(t_command *command, int status,
				char *file_path);

char			**word_splitting(char *command, int count);
char			**create_command_list(char *prt_str);
char			**create_argv_list(char **argv, char **words);
char			**copy_env(char **environ);
char			**add_env(const char *name, const char *value, char **env,
				int count);

char			*tilde_expansion(char *word, char **env);
char			*parameter_expansion(char *word, char **env);
char			*get_env_value(char *name, char **env);
char			*check_env(t_env **env, char *name);
char			*set_value(char *argv);
char			*set_name(char *argv);
char			*get_env_name(char *env);

void			destroy_arr(char **arr);
void			word_expansion(char ***words, char **env);
void			destroy_env(t_env **env);
void			destroy_command(t_command *command);
void			print_env(char **env);
void			auto_completion(char *prt_str);

t_command		*create_command_struct(char *cmd, char **env);

#endif
