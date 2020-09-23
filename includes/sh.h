/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <vgrankul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 12:35:43 by rklein            #+#    #+#             */
/*   Updated: 2020/09/22 14:15:24 by rklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_H
# define SH_H

# include <unistd.h>
# include <stdlib.h>
# include <term.h>
# include <termios.h>
# include <ctype.h>
# include <sys/ioctl.h>
# include <limits.h>
# include "../libft/libft.h"

#include <limits.h>

# include <signal.h>
# include <dirent.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <stdbool.h>

# define UP 183
# define DOWN 184
# define LEFT 186
# define RIGHT 185

# define CTRL_UP 344 
# define CTRL_DOWN 345
# define CTRL_LEFT 347
# define CTRL_RIGHT 346

# define HOME 190
# define END 188

# define DEL 295
# define BS 127
# define CR 13

# define COPY 25
# define PASTE 16

# define SQUOTE 39
# define DQUOTE 34
# define PIPE 124

typedef struct s_hs
{
	char		*hist;
	struct s_hs	*next;
	struct s_hs	*prev;
}			t_hs;

typedef struct	s_in
{
	char		*buffer;
	int			index;
	int			line;
	char		*input;
	short int		qph;
	char		*hdoc;
	char		*prompt;
	short int	prompt_size;
	char		*clipboard;
	int		cp_range[2];
	t_hs		*hs;
	t_hs		*hs_begin;
	t_hs		*hs_last;
	_Bool		hss;
}				t_in;


typedef struct	s_sh
{
	struct termios	orig;
	struct termios	raw;
	struct winsize	ws;
	t_in			*in;

}				t_sh;

void	ft_validate_term(void);
void	ft_rawmode(t_sh *sh);
int		ft_sh(t_sh *sh, char ***env);
void	ft_prompt(t_sh *sh, int prompt);
void	ft_readkey(t_sh *sh);
void	ft_resetmode(t_sh *sh);
int	ft_putint(int c);
void	ft_check_qph(t_sh *sh);
void	ft_hdoc(t_sh *sh);
/*
** line edit: input
*/
void	ft_add_char(t_sh *sh, int c);
void	ft_del_char(t_sh *sh);
void	ft_backspace(t_sh *sh);
/*
** line edit: motion
*/
void	ft_arrow_motion(t_sh *sh, int motion);
void	ft_word_motion(t_sh *sh, int motion);
void	ft_he_motion(t_sh *sh, int motion);
void	ft_line_up(t_sh *sh);		
void	ft_line_down(t_sh *sh);		
/*
** line edit: reprint
*/
void	ft_reprint(t_sh *sh);
/*
** line edit: copy
*/
void	ft_copy(t_sh *sh);
void	ft_paste(t_sh *sh);
/*
** line edit: history
*/
void	ft_history_add(t_sh *sh);
void	ft_history_scroll(t_sh *sh, int motion);

#endif
