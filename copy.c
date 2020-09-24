/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rklein <rklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 13:28:27 by rklein            #+#    #+#             */
/*   Updated: 2020/09/24 13:33:25 by rklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/sh.h"

void	ft_copy(t_sh *sh)
{
	int	tmp;
	int	len;

	if (sh->in->cp_range[0] == -1 && sh->in->cp_range[1] == -1)
		sh->in->cp_range[0] = sh->in->index;
	else if (sh->in->cp_range[0] > -1 && sh->in->cp_range[1] == -1)
		sh->in->cp_range[1] = sh->in->index;
	if (sh->in->cp_range[0] > -1 && sh->in->cp_range[1] > -1)
	{
		if (sh->in->cp_range[0] > sh->in->cp_range[1])
		{
			tmp = sh->in->cp_range[0];
			sh->in->cp_range[0] = sh->in->cp_range[1];
			sh->in->cp_range[1] = tmp;
		}
		ft_bzero(sh->in->clipboard, ft_strlen(sh->in->clipboard));
		len = sh->in->cp_range[1] - sh->in->cp_range[0] + 1;
		ft_strncpy(sh->in->clipboard, \
		&(sh->in->buffer[sh->in->cp_range[0]]), len);
		sh->in->cp_range[0] = -1;
		sh->in->cp_range[1] = -1;
	}
}

void	ft_paste(t_sh *sh)
{
	int	i;

	if (sh->in->cp_range[0] > -1 && sh->in->cp_range[1] == -1)
	{
		ft_strcpy(sh->in->clipboard, &(sh->in->buffer[sh->in->cp_range[0]]));
		sh->in->cp_range[0] = -1;
	}
	i = -1;
	while (sh->in->clipboard[++i])
		ft_add_char(sh, sh->in->clipboard[i]);
}
