/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rklein <rklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 16:21:44 by rklein            #+#    #+#             */
/*   Updated: 2020/09/17 16:22:30 by rklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/sh.h"

void	ft_history_add(t_sh *sh)
{
	t_hs *new;

	new = (t_hs*)malloc(sizeof(t_hs));
	//new->hist = ft_strdup(sh->in->input); OLD
	new->hist = ft_strsub(sh->in->input, 0, ft_strlen(sh->in->input) - 1);
	new->prev = sh->in->hs_last;
	sh->in->hs_last->next = new;
	new->next = sh->in->hs_begin;
	sh->in->hs_begin->prev = new;
	sh->in->hs_begin = new;
	sh->in->hs = sh->in->hs_begin;
	sh->in->hss = 0;
}

void	ft_history_scroll(t_sh *sh, int motion)
{
	ft_he_motion(sh, HOME);
	ft_bzero(sh->in->buffer, ft_strlen(sh->in->buffer));
	sh->in->index = 0;
	sh->in->line = 0;
	if (sh->in->hss)
	{
		if (motion == UP)
			sh->in->hs = sh->in->hs->next;
		if (motion == DOWN)
			sh->in->hs = sh->in->hs->prev;
	}
	sh->in->hss = 1;
	if (!*(sh->in->hs->hist))
		ft_reprint(sh);
	else
	{
		ft_strcpy(sh->in->buffer, sh->in->hs->hist);
		ft_reprint(sh);
		ft_he_motion(sh, END);
	}
}
