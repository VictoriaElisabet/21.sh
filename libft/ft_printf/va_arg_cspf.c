/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   va_arg_cspf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <vgrankul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 14:08:09 by vgrankul          #+#    #+#             */
/*   Updated: 2020/02/25 11:53:02 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_va_arg_float(t_format_struct *new, va_list ap)
{
	long double	n;
	char		*str;

	n = 0;
	if (new->length[0] == '\0' || new->length[0] == 'l')
		n = va_arg(ap, double);
	else if (new->length[0] == 'L')
		n = va_arg(ap, long double);
	if (new->prec == 1)
	{
		if (new->length[0] == '\0' || new->length[0] == 'l')
			str = double_float(n, new->precision, new);
		else
			str = long_double(n, new->precision, new);
	}
	else
	{
		if (new->length[0] == '\0' || new->length[0] == 'l')
			str = double_float(n, 6, new);
		else
			str = long_double(n, 6, new);
	}
	return (ft_check_flags_float(str, new));
}

int	ft_va_arg_char(t_format_struct *new, va_list ap)
{
	char	n;
	int		a;

	if (new->conv_char == '%')
		n = '%';
	else
	{
		a = va_arg(ap, int);
		n = (unsigned char)a;
	}
	return (ft_check_flags_char(n, new));
}

int	ft_va_arg_string(t_format_struct *new, va_list ap)
{
	char *str;

	str = va_arg(ap, char*);
	return (ft_check_flags_string(str, new));
}

int	ft_va_arg_mem(t_format_struct *new, va_list ap)
{
	long long	n;
	char		*str;
	int			strlen;

	n = va_arg(ap, long long);
	str = ft_string_tolower(ft_hex(n));
	strlen = ft_check_flags_string(str, new);
	free(str);
	return (strlen);
}
