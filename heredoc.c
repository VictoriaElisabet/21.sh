/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rklein <rklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 11:01:28 by rklein            #+#    #+#             */
/*   Updated: 2020/09/25 16:44:14 by rklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/sh.h"

static void	ft_hd_setup(t_sh *sh, char *str)
{
	int		len;

	sh->in = (t_in*)malloc(sizeof(t_in));
	tcgetattr(STDIN_FILENO, &sh->orig);
	ft_init(sh);
	sh->in->qph = 8;
	if (str[0] == 34 || str[0] == 39)
	{
		len = ft_strlen(str) - 2;
		ft_strncpy(sh->in->hdoc, &str[1], len);
	}
	else
		ft_strcpy(sh->in->hdoc, str);
}

static char	*ft_hd_free(t_sh *sh)
{
	char	*str;

	str = ft_memalloc(ft_strlen(sh->in->input) + 1);
	str[0] = '\n';
	ft_strcat(str, sh->in->input);
	free(sh->in->prompt);
	free(sh->in->buffer);
	free(sh->in->input);
	free(sh->in->clipboard);
	free(sh->in->hdoc);
	free(sh->in->hs->hist);
	free(sh->in->hs);
	free(sh->in);
	free(sh);
	return (str);
}

char		*ft_hd_doc(char *str)
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
