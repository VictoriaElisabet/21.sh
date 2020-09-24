/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reprint.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rklein <rklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 12:51:07 by rklein            #+#    #+#             */
/*   Updated: 2020/09/24 15:35:55 by rklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/sh.h"

static void	ft_print_str(t_sh *sh)
{
	int	i;

	i = -1;
	while (sh->in->buffer[++i])
	{
		if (!(sh->in->index < (int)ft_strlen(sh->in->buffer) &&
					sh->in->buffer[i] == '\n' && !sh->in->buffer[i + 1]))
			write(1, &sh->in->buffer[i], 1);
		if (sh->in->buffer[i] == '\n' && sh->in->buffer[i + 1])
			tputs(tgetstr("cr", NULL), 1, ft_putint);
	}
}

static int	ft_count_line(t_sh *sh, int n)
{
	int	i;
	int	count;
	int row;

	count = 1;
	row = 0;
	i = 0;
	while (sh->in->buffer[i] && i < n)
	{
		if (sh->in->buffer[i] == '\n' ||
				(count + sh->in->prompt_size) % sh->ws.ws_col == 0)
		{
			row++;
			count = 0 - sh->in->prompt_size;
		}
		count++;
		i++;
	}
	return (row);
}

static void	ft_cursor_cont(t_sh *sh, int cursor, int i)
{
	if (i == (int)ft_strlen(sh->in->buffer) && sh->in->buffer[i - 1] == '\n')
		tputs(tgetstr("cr", NULL), 1, ft_putint);
	if (cursor / sh->ws.ws_col && cursor % sh->ws.ws_col == 0)
	{
		tputs(tgetstr("cr", NULL), 1, ft_putint);
		tputs(tgetstr("do", NULL), 1, ft_putint);
	}
}

static void	ft_cursor(t_sh *sh)
{
	int	cursor;
	int	i;
	int nl;

	cursor = 0;
	i = 0 - sh->in->prompt_size;
	nl = 0;
	while (i < sh->in->index)
	{
		if (((i >= 0 && sh->in->buffer[i] == '\n') ||
			(cursor / sh->ws.ws_col && cursor % sh->ws.ws_col == 0)) &&
			!(i == (int)ft_strlen(sh->in->buffer) - 1 &&
				sh->in->buffer[i] == '\n'))
		{
			tputs(tgetstr("cr", NULL), 1, ft_putint);
			tputs(tgetstr("do", NULL), 1, ft_putint);
			cursor = nl ? -1 : 0;
			nl = sh->in->buffer[i] == '\n' ? 1 : nl;
		}
		if (!(i >= 0 && sh->in->buffer[i] == '\n'))
			tputs(tgetstr("nd", NULL), 1, ft_putint);
		cursor++;
		i++;
	}
	ft_cursor_cont(sh, cursor, i);
}

void		ft_reprint(t_sh *sh)
{
	int	row;

	row = sh->in->line;
	tputs(tgetstr("cr", NULL), 1, ft_putint);
	while (row--)
		tputs(tgetstr("up", NULL), 1, ft_putint);
	tputs(tgetstr("cd", NULL), 1, ft_putint);
	ft_putstr_fd(sh->in->prompt, STDOUT_FILENO);
	ft_print_str(sh);
	row = ft_count_line(sh, (int)ft_strlen(sh->in->buffer) - 1);
	tputs(tgetstr("cr", NULL), 1, ft_putint);
	while (row--)
		tputs(tgetstr("up", NULL), 1, ft_putint);
	ft_cursor(sh);
	sh->in->line = ft_count_line(sh, sh->in->index);
}
