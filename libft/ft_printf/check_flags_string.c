/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <vgrankul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 14:07:26 by vgrankul          #+#    #+#             */
/*   Updated: 2020/02/25 11:39:17 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_check_string_prec(t_format_struct *new, char *str)
{
	char *tmp;

	tmp = str;
	if (new->precision != 0 && new->precision < (int)ft_strlen(str))
	{
		str = ft_copy_string(str, new->precision);
	}
	else if (new->precision == 0 && new->prec == 1)
		str = ft_copy_string(str, new->precision);
	else
		return (str);
	free(tmp);
	return (str);
}

char	*ft_check_string_width(t_format_struct *new, char *str)
{
	char *tmp;

	tmp = str;
	if (new->width != 0 && new->width > (int)ft_strlen(str))
		str = ft_set_space(str, new, ' ');
	else
		return (str);
	free(tmp);
	return (str);
}

int		ft_check_flags_string(char *str, t_format_struct *new)
{
	char	*s;
	int		strlen;

	s = 0;
	if (str == NULL)
		s = ft_strdup("(null)");
	else
		s = ft_strdup(str);
	if (new->conv_char == 'p')
		s = ft_add_ox(s, new);
	if (new->prec == 1)
		s = ft_check_string_prec(new, s);
	if (new->width != 0)
		s = ft_check_string_width(new, s);
	ft_putstr(s);
	strlen = ft_strlen(s);
	free(s);
	return (strlen);
}
