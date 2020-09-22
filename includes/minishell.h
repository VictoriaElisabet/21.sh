/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <vgrankul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 10:24:05 by vgrankul          #+#    #+#             */
/*   Updated: 2020/09/16 15:19:48 by vgrankul         ###   ########.fr       */
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
# include <signal.h>
# include "../libft/libft.h"

# define BUF_SIZE		32

# define SQ				1
# define DQ				2
# define ESC			4

# define PIPE_OP		1
# define OR_OP			2
# define PIPE_AMP_OP	4
# define AMP_OP 		8
# define AND_OP 		16
# define SEMI			32
# define NEWLINE		64

# define FD_ERR		"21sh: bad filedescriptor"
# define FILE_ERR	"21sh: failed to open file"
# define SYNTAX_ERR	"21sh: syntax error"
# define DUP2_FAIL	"21sh: dup2 failed"
# define CLOSE_ERR	"21sh: close failed"
# define PIPE_ERR	"21sh: pipe failed"

enum			redir_type
{
	L,
	LL,
	L_AND,
	L_AND_H,
	LL_H,
	LG,
	G,
	GG,
	G_AND,
	G_AND_H,
	CLOBBER,
};

enum			e_token_type
{
	WORD_ASSIGN,
	WORD,
	OPERATOR,
	REDIR,
	IO_NUM,
};

typedef struct	s_env
{
	char *name;
	char *value;

}				t_env;

typedef struct	s_token
{
	int				type;
	char			*token;
	int				flags;
	struct s_token	*next;
	struct s_token	*prev;

}				t_token;

typedef struct	s_command
{
	t_token		*tokens;
	char		**argv;
	int			argc;
	int			ctrl_op;
	int			fd[3];
	int			fork;
}				t_command;

int				str_chr(char *str, int c);
int				ft_setenv(int argc, char *name, char *value, char ***env);
int				count_arr(char **arr);
int				ft_unsetenv(int argc, char **argv, char ***env);
int				ft_cd (int argc, char **argv, char ***env);
int				ft_echo(char **argv);
int				is_builtin(t_command *command);
int				run_builtin(t_command *command, t_command **commands,
				char ***env, int status);
int				exec_command(t_command *command, t_command **commands, pid_t pid, char ***env);
int				find_env(const char *name, char **env);
int				ft_env(t_command *command, t_command **commands, char **env);
int				ft_exit(t_command *command, t_command **commands, char ***env,
				int status);
int				handle_command_list(t_command **command_list, char ***env);
int				count_list(char **list);
int				print_exec_error(t_command *command, int status,
				char *file_path);
int				create_pipe(t_command **commands, char ***env, int *i);
int				is_redir(int c);
int				is_separator(int c);
int				create_redir(t_token **head, char *command);
int				create_word(t_token **head, char *command);
int				set_redirections(t_command *command);
int				get_quote_index(char *token, int flags);
int				count_squoting_word(char *command, int *flags);
int				is_redir_in(int r_type);
int				is_redir_out(int r_type);
int				dup2_fd(int n, int fd, int dash, int r_type);
int				open_fd(t_token *tmp, int fd, int r_type, int *dash);
int				open_heredoc_fd(t_token *tmp, int n, int dash, int r_type);
int				print_redir_error(char *str);
int				get_redir(char *token);
int				is_digits(t_token *tmp, int *dash);
int				file_aggr(t_token *tmp, int fd, int *dash);

char			**word_splitting(char *command, int count);

char			**create_argv_list(char **argv, char **words);
char			**copy_env(char **environ);
char			**add_env(const char *name, const char *value, char **env,
				int count);

char			*tilde_expansion(char *word, char **env);
char			*parameter_expansion(t_token *token, char *word, char **env);
char			*get_env_value(char *name, char **env);
char			*check_env(t_env **env, char *name);
char			*set_value(char *argv);
char			*set_name(char *argv);
char			*get_env_name(char *env);

void			destroy_arr(char **arr);
void			token_expansion(t_token **head, char **env);
void			destroy_env(t_env **env);
void			destroy_command(t_command **command);
void			print_env(char **env);
void			auto_completion(char *prt_str);

void			remove_word(char ***words, int word);
void			set_struct(t_command *command);
void			destroy_tok_list(t_token *head);
void			add_token(t_token **head, int tok_type, char *tok, int flags);
void			reset_redirections(int fd[3]);
void			set_fd(int fd[3]);
void			remove_quoting(t_token **head);
void			remove_squotes(t_token **tokens, int sindex);
void			remove_dquotes(t_token **tokens, int sindex);
void			remove_esc(t_token **tokens);
void			set_fd(int fd[3]);
void			set_redir_list(char redir[11][4]);
void			reset_redirections(int fd[3]);

t_command		**create_command_list(t_token **tokens, char **env);

t_token			*create_tokens(char *command);

void		print_token(t_token *head); // ta bort

#endif
