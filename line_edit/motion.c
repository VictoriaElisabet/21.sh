/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   motion.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rklein <rklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 13:59:40 by rklein            #+#    #+#             */
/*   Updated: 2020/09/24 13:03:17 by rklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

void		ft_arrow_motion(t_sh *sh, int motion)
{
	if (motion == LEFT && sh->in->index > 0)
		sh->in->index--;
	if (motion == RIGHT && sh->in->index < (int)ft_strlen(sh->in->buffer))
		sh->in->index++;
	ft_reprint(sh);
}

void		ft_word_motion(t_sh *sh, int motion)
{
	int	i;

	i = 0;
	while (ft_isspace(sh->in->buffer[i]))
		i++;
	if (motion == CTRL_LEFT)
	{
		if (sh->in->index > i && !ft_isspace(sh->in->buffer[sh->in->index]) &&
				ft_isspace(sh->in->buffer[sh->in->index - 1]))
			ft_arrow_motion(sh, LEFT);
		while (sh->in->index > i && !(!ft_isspace(sh->in->buffer[sh->in->index])
					&& ft_isspace(sh->in->buffer[sh->in->index - 1])))
			ft_arrow_motion(sh, LEFT);
	}
	if (motion == CTRL_RIGHT)
	{
		if (sh->in->index < (int)ft_strlen(sh->in->buffer) &&
				!ft_isspace(sh->in->buffer[sh->in->index]) &&
				ft_isspace(sh->in->buffer[sh->in->index - 1]))
			ft_arrow_motion(sh, RIGHT);
		while (sh->in->index < (int)ft_strlen(sh->in->buffer) &&
				!(!ft_isspace(sh->in->buffer[sh->in->index]) &&
					ft_isspace(sh->in->buffer[sh->in->index - 1])))
			ft_arrow_motion(sh, RIGHT);
	}
}

void		ft_he_motion(t_sh *sh, int motion)
{
	if (motion == HOME)
	{
		while (sh->in->index > 0)
			ft_arrow_motion(sh, LEFT);
	}
	if (motion == END)
	{
		while (sh->in->index < (int)ft_strlen(sh->in->buffer))
			ft_arrow_motion(sh, RIGHT);
	}
}

void		ft_line_up(t_sh *sh)
{
	if (sh->in->index - sh->ws.ws_col > 0)
	{
		sh->in->index = sh->in->index - sh->ws.ws_col;
		ft_reprint(sh);
	}
	else
	{
		if (sh->in->buffer[sh->in->index] == '\n')
			ft_arrow_motion(sh, LEFT);
		while (sh->in->index > 0 && sh->in->buffer[sh->in->index] != '\n')
			ft_arrow_motion(sh, LEFT);
	}
}

void		ft_line_down(t_sh *sh)
{
	if (sh->in->index + sh->ws.ws_col < (int)ft_strlen(sh->in->buffer))
	{
		sh->in->index = sh->in->index + sh->ws.ws_col;
		ft_reprint(sh);
	}
	else
	{
		if (sh->in->buffer[sh->in->index] == '\n')
			ft_arrow_motion(sh, RIGHT);
		while (sh->in->index < (int)ft_strlen(sh->in->buffer) &&
				sh->in->buffer[sh->in->index] != '\n')
			ft_arrow_motion(sh, RIGHT);
	}
}
