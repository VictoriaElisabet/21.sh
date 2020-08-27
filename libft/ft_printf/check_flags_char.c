/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_flags_char.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <vgrankul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 14:07:26 by vgrankul          #+#    #+#             */
/*   Updated: 2020/02/25 11:42:20 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		char_width(char n, t_format_struct *new)
{
	int i;

	i = 0;
	if (new->f_minus == 1)
	{
		new->f_zero = 0;
		write(1, &n, 1);
		while (new->width - 1)
		{
			write(1, " ", 1);
			new->width--;
			i++;
		}
	}
	return (i);
}

int		char_f_zero(t_format_struct *new)
{
	int i;

	i = 0;
	while (new->width - 1)
	{
		write(1, "0", 1);
		new->width--;
		i++;
	}
	return (i);
}

int		ft_check_flags_char(char n, t_format_struct *new)
{
	int i;

	i = 0;
	if (new->width != 0 && new->f_minus == 1)
		i = char_width(n, new);
	else if (new->f_zero == 1 && new->conv_char == '%')
		i = char_f_zero(new);
	else if (new->width != 0)
	{
		while (new->width - 1)
		{
			write(1, " ", 1);
			new->width--;
			i++;
		}
	}
	if (new->f_minus != 1)
		write(1, &n, 1);
	return (1 + i);
}
