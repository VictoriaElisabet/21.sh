# include "./includes/sh.h"

void	ft_arrow_motion(t_sh *sh, int motion)
{
	if (motion == LEFT && sh->in->index > 0)
		sh->in->index--;
	if (motion == RIGHT && sh->in->index < (int)ft_strlen(sh->in->buffer))
		sh->in->index++;
	ft_reprint(sh);
}

void	ft_word_motion(t_sh *sh, int motion)
{
	int	i;

	i = 0;
//	while (sh->in->buffer[i] == ' ')
	while (ft_isspace(sh->in->buffer[i])) //NEW
		i++;
	if (motion == CTRL_LEFT)
	{
//		if (sh->in->index > i && sh->in->buffer[sh->in->index] != ' ' &&
//				sh->in->buffer[sh->in->index - 1] == ' ')
		if (sh->in->index > i && !ft_isspace(sh->in->buffer[sh->in->index]) && //NEW
				ft_isspace(sh->in->buffer[sh->in->index - 1])) //NEW
			ft_arrow_motion(sh, LEFT);
//		while (sh->in->index > i && !(sh->in->buffer[sh->in->index] != ' ' &&
//				sh->in->buffer[sh->in->index - 1] == ' '))
		while (sh->in->index > i && !(!ft_isspace(sh->in->buffer[sh->in->index]) && //NEW
					ft_isspace(sh->in->buffer[sh->in->index - 1]))) //NEW
			ft_arrow_motion(sh, LEFT);
	}
	if (motion == CTRL_RIGHT)
	{
//		if (sh->in->index < ft_strlen(sh->in->buffer) &&
//				sh->in->buffer[sh->in->index] != ' ' && 
//				sh->in->buffer[sh->in->index - 1] == ' ')
		if (sh->in->index < (int)ft_strlen(sh->in->buffer) && //NEW
				!ft_isspace(sh->in->buffer[sh->in->index]) && //NEW
				ft_isspace(sh->in->buffer[sh->in->index - 1])) //NEW
			ft_arrow_motion(sh, RIGHT);
//		while (sh->in->index < ft_strlen(sh->in->buffer) && 
//				!(sh->in->buffer[sh->in->index] != ' ' &&
//				sh->in->buffer[sh->in->index - 1] == ' '))
		while (sh->in->index < (int)ft_strlen(sh->in->buffer) && //NEW
				!(!ft_isspace(sh->in->buffer[sh->in->index]) && //NEW
					ft_isspace(sh->in->buffer[sh->in->index - 1]))) //NEW
			ft_arrow_motion(sh, RIGHT);
	}
}

void	ft_he_motion(t_sh *sh, int motion)
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

void	ft_line_motion(t_sh *sh, int motion)		
{
	if (motion == CTRL_UP)
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
			//ft_he_motion(sh, HOME);
	}
	if (motion == CTRL_DOWN)
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
			while (sh->in->index < (int)ft_strlen(sh->in->buffer) && sh->in->buffer[sh->in->index] != '\n')
				ft_arrow_motion(sh, RIGHT);

		}
	//		ft_he_motion(sh, END);
	}
}
