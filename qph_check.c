#include "./includes/sh.h"

static char	ft_q_track(char s, char q)
{
	if (s == 34 || s == 39)
	{
		if (q == 0)
			q = s;
		else if (q == s)
			q = 0;
	}
	return (q);
}

static void	ft_copy_hdoc(t_sh *sh, char *str)
{
	int	i;
	int	j;
	char	q;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	q = 0;
	j = 0;
	while (str[i])
	{
		q = ft_q_track(str[i], q);
		if (!q && (str[i] == ' ' || str[i] == '\t'))
			break;
		else if (str[i] == 34 || str[i] == 39)
		{
			if (q && str[i] != q)
				sh->in->hdoc[j++] = str[i];
		}
		else
			sh->in->hdoc[j++] = str[i];
		i++;
	}
}

static void	ft_hdoc(t_sh *sh)
{
	char	*first;
	char	*last;

	if (!(sh->in->qph / 8))
	{
		first = ft_strchr(sh->in->buffer, 60);
		last = ft_strrchr(sh->in->buffer, 60);
		if (last - first == 1)
		{
			ft_copy_hdoc(sh, last + 1);
			sh->in->qph = (sh->in->hdoc[0]) ? sh->in->qph + 8 : sh->in->qph;
		}
	}
	else if (ft_strequ(sh->in->buffer, sh->in->hdoc))
	{
		sh->in->qph -= 8;
		ft_bzero(sh->in->hdoc, ft_strlen(sh->in->hdoc));
	}
}

static void	ft_quotes(t_sh *sh, int q)
{
	if (!(sh->in->qph % 4))
		sh->in->qph += q;
	else if (sh->in->qph % 4 == q)
		sh->in->qph -= q;
}

void	ft_check_qph(t_sh *sh)
{
	int	i;

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
	ft_hdoc(sh);
}
