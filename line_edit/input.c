/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <vgrankul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 10:24:31 by rklein            #+#    #+#             */
/*   Updated: 2020/09/24 15:29:30 by rklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

void		ft_add_char(t_sh *sh, int c)
{
	if (sh->in->buffer[sh->in->index])
		ft_memmove(sh->in->buffer + sh->in->index + 1, \
		sh->in->buffer + sh->in->index, \
		ft_strlen(sh->in->buffer + sh->in->index));
	sh->in->buffer[sh->in->index] = c == 9 ? ' ' : c;
	sh->in->index++;
	ft_reprint(sh);
}

void		ft_del_char(t_sh *sh)
{
	if (sh->in->buffer[sh->in->index])
	{
		ft_memmove(sh->in->buffer + sh->in->index, \
		sh->in->buffer + sh->in->index + 1, \
		ft_strlen(sh->in->buffer + sh->in->index));
		sh->in->buffer[ft_strlen(sh->in->buffer)] = 0;
		ft_reprint(sh);
	}
}

void		ft_backspace(t_sh *sh)
{
	if (sh->in->index > 0)
	{
		sh->in->index--;
		ft_memmove(sh->in->buffer + sh->in->index, \
		sh->in->buffer + sh->in->index + 1, \
		ft_strlen(sh->in->buffer + sh->in->index));
		sh->in->buffer[ft_strlen(sh->in->buffer)] = 0;
		ft_reprint(sh);
	}
}
