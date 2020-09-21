/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <vgrankul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 15:04:40 by rklein            #+#    #+#             */
/*   Updated: 2020/09/21 13:42:21 by rklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/sh.h"


static void	ft_key_action(t_sh *sh, int sum)
{
	if (ft_isprint(sum))
		ft_add_char(sh, sum);
	if (sum == BS && sh->in->index > 0)
		ft_backspace(sh);
	if (sum == DEL)
		ft_del_char(sh);
	if (sum == LEFT || sum == RIGHT)
		ft_arrow_motion(sh, sum);
	if (sum == CTRL_LEFT || sum == CTRL_RIGHT)
		ft_word_motion(sh, sum);
	if (sum == CTRL_UP || sum == CTRL_DOWN)
		ft_line_motion(sh, sum);
	if (sum == HOME || sum == END)
		ft_he_motion(sh, sum);
	if (sum == UP || sum == DOWN)
		ft_history_scroll(sh, sum);
	if (sum == COPY)
		ft_copy(sh);
	if (sum == PASTE)
		ft_paste(sh);
}

static _Bool ft_readsum(t_sh *sh, int sum)
{
	if (sum == 3/*^C*/)
	{
		sh->in->qph = 0;
		ft_bzero(sh->in->input, ft_strlen(sh->in->input));
		return (1);
	}
	if (sum == 4/*^D*/)//handle heredoc
	{
		if (!sh->in->buffer[0] && !sh->in->input[0])
		{
			ft_resetmode(sh); //NEW moved from main
			exit(1);
		}
		if (!sh->in->buffer[0] && sh->in->input && sh->in->qph / 8 && 
				ft_strequ(sh->in->hdoc, "EOF"))
		{
			ft_hdoc(sh);
			return (1);
		}
		else
			sum = DEL;
	}
	if (sum == CR)
	{
		ft_he_motion(sh, END);
		ft_check_qph(sh);
		if (sh->in->qph)
			sh->in->buffer[ft_strlen(sh->in->buffer)] = '\n';
		ft_strcat(sh->in->input, sh->in->buffer);
		return (1);
	}
	ft_key_action(sh, sum);
	return (0);
}

void	ft_readkey(t_sh *sh)
{
	char	key[9];
	int		bytes;
	int		i;
	int		sum;

	while (1)
	{
		ioctl(STDIN_FILENO, TIOCGWINSZ, &sh->ws);//not sure if this is the best way
		bytes = read(STDIN_FILENO, key, 8);
		key[bytes] = '\0';
		i = -1;
		sum = 0;
		while (key[++i])
			sum += key[i];
		if (ft_readsum(sh, sum))
			break;
	}
}
