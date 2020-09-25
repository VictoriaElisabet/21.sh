/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rklein <rklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 11:01:28 by rklein            #+#    #+#             */
/*   Updated: 2020/09/25 13:47:00 by rklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/sh.h"

static void	ft_hd_setup(t_sh *sh, char *str)
{
	sh->in = (t_in*)malloc(sizeof(t_in));
	tcgetattr(STDIN_FILENO, &sh->orig);
	ft_init(sh);
	sh->in->qph = 8;
	ft_strcpy(sh->in->hdoc, str);
}

static char	*ft_hd_free(t_sh *sh)
{
	char	*str;

	str = ft_strdup(sh->in->input);
	//Possibly need to free strings in structs
	free(sh->in);
	free(sh);
	return (str);
}

char	*ft_hd_doc(char *str)
{
	t_sh	*sh;
	
	sh = (t_sh*)malloc(sizeof(t_sh));
	ft_hd_setup(sh, str);
	while (1)
	{
		ft_rawmode(sh);
		ft_prompt(sh, 1);
		ft_reprint(sh);
		ft_readkey(sh);
		ft_resetmode(sh);
		ft_reset_buffer(sh);
		if (!sh->in->qph)
			return (ft_hd_free(sh));
		else
		{
			tputs(tgetstr("cr", NULL), 1, ft_putint);
			tputs(tgetstr("do", NULL), 1, ft_putint);
		}
	}
}
