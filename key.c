/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <vgrankul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 15:04:40 by rklein            #+#    #+#             */
/*   Updated: 2020/09/24 15:35:52 by rklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/sh.h"

static void		ft_key_action(t_sh *sh, int sum)
{
	if (ft_isprint(sum) || sum == 9)
		ft_add_char(sh, sum);
	if (sum == BS && sh->in->index > 0)
		ft_backspace(sh);
	if (sum == DEL)
		ft_del_char(sh);
	if (sum == LEFT || sum == RIGHT)
		ft_arrow_motion(sh, sum);
	if (sum == CTRL_LEFT || sum == CTRL_RIGHT)
		ft_word_motion(sh, sum);
	if (sum == CTRL_UP)
		ft_line_up(sh);
	if (sum == CTRL_DOWN)
		ft_line_down(sh);
	if (sum == HOME || sum == END)
		ft_he_motion(sh, sum);
	if (sum == UP || sum == DOWN)
		ft_history_scroll(sh, sum);
	if (sum == COPY)
		ft_copy(sh);
	if (sum == PASTE)
		ft_paste(sh);
}

static void		ft_write_to_input(t_sh *sh)
{
	ft_he_motion(sh, END);
	ft_check_qph(sh);
	if (sh->in->qph)
		sh->in->buffer[ft_strlen(sh->in->buffer)] = '\n';
	ft_strcat(sh->in->input, sh->in->buffer);
}

static int		ft_ctrl_d(t_sh *sh)
{
	if (!sh->in->buffer[0] && !sh->in->input[0])
	{
		ft_resetmode(sh);
		exit(1);
	}
	if (!sh->in->buffer[0] && sh->in->input && sh->in->qph / 8 &&
			ft_strequ(sh->in->hdoc, "EOF"))
	{
		ft_hdoc(sh);
		return (-1);
	}
	else
		return (DEL);
}

static _Bool	ft_readsum(t_sh *sh, int sum)
{
	if (sum == 3)
	{
		sh->in->qph = 0;
		ft_bzero(sh->in->input, ft_strlen(sh->in->input));
		return (1);
	}
	if (sum == 4)
	{
		sum = ft_ctrl_d(sh);
		if (sum == -1)
			return (1);
	}
	if (sum == CR)
	{
		ft_write_to_input(sh);
		return (1);
	}
	ft_key_action(sh, sum);
	return (0);
}

void			ft_readkey(t_sh *sh)
{
	char	key[9];
	int		bytes;
	int		i;
	int		sum;

	while (1)
	{
		ioctl(STDIN_FILENO, TIOCGWINSZ, &sh->ws);
		bytes = read(STDIN_FILENO, key, 8);
		key[bytes] = '\0';
		i = -1;
		sum = 0;
		while (key[++i])
			sum += key[i];
		if (ft_readsum(sh, sum))
			break ;
	}
}
