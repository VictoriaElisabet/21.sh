/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_flags_diouxx.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <vgrankul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 14:07:26 by vgrankul          #+#    #+#             */
/*   Updated: 2020/02/25 12:51:09 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*diouxx_width(char *str, t_format_struct *new)
{
	char *tmp;

	tmp = str;
	if (new->f_minus == 1)
	{
		new->f_zero = 0;
		str = ft_set_space(str, new, ' ');
	}
	else if (new->f_zero == 1)
	{
		str = ft_set_space(str, new, '0');
	}
	else if (new->f_zero != 1)
		str = ft_set_space(str, new, ' ');
	free(tmp);
	return (str);
}

char	*diouxx_prec(char *str, t_format_struct *new)
{
	int		len;
	int		preclen;
	char	*tmp;

	tmp = str;
	if (str[0] == '-' || str[0] == '+')
		new->precision = new->precision + 1;
	len = (new->precision - ft_strlen(str)) + ft_strlen(str);
	preclen = new->precision - ft_strlen(str);
	if (new->prec != 2)
		new->f_zero = 0;
	if (new->precision == 0 && new->prec == 1 && new->f_hash != 1)
	{
		if (ft_strcmp(str, "0") == 0)
			str = ft_copy_string(str, 0);
		else
			str = ft_copy_string(str, ft_strlen(str));
	}
	if (new->precision == (int)ft_strlen(str) ||
			new->precision < (int)ft_strlen(str))
		return (str);
	if (new->precision > (int)ft_strlen(str))
		str = ft_add_zero_diouxx(str, len, preclen);
	free(tmp);
	return (str);
}

void	octal_hash_exception(char *str, t_format_struct *new)
{
	if (new->precision == 0 && new->prec == 0 && str[0] != '0')
	{
		new->precision = ft_strlen(str) + 1;
		new->prec = 2;
	}
	if (new->precision <= (int)ft_strlen(str) && str[0] != '0')
	{
		new->precision = ft_strlen(str) + 1;
		new->prec = 1;
	}
}

char	*plus_sign_diouxx(char *str, t_format_struct *new)
{
	new->f_space = 0;
	str = ft_set_sign(str, '+');
	return (str);
}

int		ft_check_flags_diouxx(char *str, t_format_struct *new)
{
	int strlen;

	if (new->conv_char == 'o' && new->f_hash == 1)
		octal_hash_exception(str, new);
	if (new->precision >= 0 && (new->prec == 1 || new->prec == 2))
		str = diouxx_prec(str, new);
	if ((new->conv_char == 'd' || new->conv_char == 'i') && new->f_plus == 1)
		str = plus_sign_diouxx(str, new);
	if ((new->conv_char == 'd' || new->conv_char == 'i') && new->f_space == 1)
		str = ft_set_sign(str, ' ');
	if ((new->conv_char == 'x' || new->conv_char == 'X') && new->f_hash == 1)
		str = ft_add_ox(str, new);
	if (new->width != 0 && new->width > (int)ft_strlen(str))
		str = diouxx_width(str, new);
	ft_putstr(str);
	strlen = ft_strlen(str);
	free(str);
	return (strlen);
}
