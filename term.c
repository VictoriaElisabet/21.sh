/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <vgrankul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 10:54:16 by rklein            #+#    #+#             */
/*   Updated: 2020/09/16 15:13:54 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/sh.h"

void	ft_validate_term(void)
{
	char	*termtype;
	char	term_buffer[2048];
	int		success;

	if (!(termtype = getenv("TERM")))
	{
		write(1, "Specify a terminal type with 'export TERM <yourtype>'.\n", 56);
		exit(1);
	}
	if ((success = tgetent(term_buffer, termtype)) < 1)
	{
		if (success < 0)
			write(1, "Could not access the termcap database.\n", 39);
		if (success == 0)
			write(1, "Terminal type is not defined.\n", 30);
		exit(1);
	}
}

void	ft_resetmode(t_sh *sh)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &sh->orig);
}

void	ft_rawmode(t_sh	*sh)
{
//	tcgetattr(STDIN_FILENO, &sh->orig);
	sh->raw = sh->orig;
	ioctl(STDIN_FILENO, TIOCGWINSZ, &sh->ws);//retrieves terminal window size
	sh->raw.c_iflag &= ~(ICRNL | IXON);//ICRNL: Ctrl-M; IXON: Ctrl-S and Ctrl-X
	sh->raw.c_oflag &= ~(OPOST); //OPOST (O-output, POST-postprocessing)
	sh->raw.c_lflag &= ~(ICANON | ECHO | IEXTEN | ISIG); //ISIG: Ctrl-C, Ctrl-Z, etc. IEXTEN: Ctrl-V and Ctrl-O
	sh->raw.c_cc[VMIN] = 1;
	sh->raw.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &sh->raw);
}
