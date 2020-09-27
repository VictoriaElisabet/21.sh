/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qph_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rklein <rklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 10:55:32 by rklein            #+#    #+#             */
/*   Updated: 2020/09/25 15:13:48 by rklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

void		ft_hdoc(t_sh *sh)
{
	if (ft_strequ(sh->in->buffer, sh->in->hdoc) ||
			(ft_strequ(sh->in->hdoc, "EOF") && !sh->in->buffer[0]))
		sh->in->qph -= 8;
}

static void	ft_quotes(t_sh *sh, int q)
{
	if (!(sh->in->qph % 4))
		sh->in->qph += q;
	else if (sh->in->qph % 4 == q)
		sh->in->qph -= q;
}

void		ft_check_qph(t_sh *sh)
{
	int	i;

	if (sh->in->qph / 8)
		ft_hdoc(sh);
	else
	{
		i = -1;
		while (sh->in->buffer[++i])
		{
			if (sh->in->buffer[i] == 39 && sh->in->buffer[i - 1] != 92)
				ft_quotes(sh, 1);
			if (sh->in->buffer[i] == 34 && sh->in->buffer[i - 1] != 92)
				ft_quotes(sh, 2);
			if (sh->in->buffer[i] == 124 && sh->in->buffer[i - 1] != 92 &&
					sh->in->buffer[i - 1] != 124 && !sh->in->qph)
				sh->in->qph += 4;
			if ((sh->in->buffer[i] != 124 ||
					(sh->in->buffer[i] == 124 && sh->in->buffer[i - 1] == 124))
					&& sh->in->buffer[i] != ' ' && sh->in->qph == 4)
				sh->in->qph -= 4;
		}
	}
}
