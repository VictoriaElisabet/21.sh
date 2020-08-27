/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   va_arg_diouxx.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <vgrankul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 14:07:26 by vgrankul          #+#    #+#             */
/*   Updated: 2020/02/27 16:09:27 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_va_arg_int(t_format_struct *new, va_list ap)
{
	char		*str;
	long long	n;
	int			a;

	n = 0;
	if (new->length[0] == 0)
		n = va_arg(ap, int);
	else if (new->length[0] == 'l' && new->length[1] == 'l')
		n = va_arg(ap, long long);
	else if (new->length[0] == 'l' && new->length[1] == '\0')
		n = va_arg(ap, long);
	else if (new->length[0] == 'h' && new->length[1] == 'h')
	{
		a = va_arg(ap, int);
		n = (char)a;
	}
	else if (new->length[0] == 'h' && new->length[1] == '\0')
	{
		a = va_arg(ap, int);
		n = (short)a;
	}
	str = ft_itoa(n);
	return (ft_check_flags_diouxx(str, new));
}

int	ft_va_arg_octal(t_format_struct *new, va_list ap)
{
	long long	n;
	int			a;
	char		*str;

	n = 0;
	if (new->length[0] == '\0')
		n = va_arg(ap, unsigned int);
	else if (new->length[0] == 'l' && new->length[1] == 'l')
		n = va_arg(ap, unsigned long long);
	else if (new->length[0] == 'l' && new->length[1] == '\0')
		n = va_arg(ap, unsigned long);
	else if (new->length[0] == 'h' && new->length[1] == 'h')
	{
		a = va_arg(ap, unsigned int);
		n = (unsigned char)a;
	}
	else if (new->length[0] == 'h' && new->length[1] == '\0')
	{
		a = va_arg(ap, unsigned int);
		n = (unsigned short)a;
	}
	str = ft_octal(n);
	return (ft_check_flags_diouxx(str, new));
}

int	ft_va_arg_unsigned_int(t_format_struct *new, va_list ap)
{
	unsigned long long	n;
	unsigned int		a;
	char				*str;

	n = 0;
	if (new->length[0] == '\0')
		n = va_arg(ap, unsigned int);
	else if (new->length[0] == 'l' && new->length[1] == 'l')
		n = va_arg(ap, unsigned long long);
	else if (new->length[0] == 'l' && new->length[1] == '\0')
		n = va_arg(ap, unsigned long);
	else if (new->length[0] == 'h' && new->length[1] == 'h')
	{
		a = va_arg(ap, unsigned int);
		n = (unsigned char)a;
	}
	else if (new->length[0] == 'h' && new->length[1] == '\0')
	{
		a = va_arg(ap, unsigned int);
		n = (unsigned short)a;
	}
	str = ft_uitoa(n);
	return (ft_check_flags_diouxx(str, new));
}

int	ft_va_arg_hex(t_format_struct *new, va_list ap, unsigned long long n)
{
	unsigned int		a;
	char				*str;

	if (new->length[0] == '\0')
		n = va_arg(ap, unsigned int);
	else if (new->length[0] == 'l' && new->length[1] == 'l')
		n = va_arg(ap, unsigned long long);
	else if (new->length[0] == 'l' && new->length[1] == '\0')
		n = va_arg(ap, unsigned long);
	else if (new->length[0] == 'h' && new->length[1] == 'h')
	{
		a = va_arg(ap, unsigned int);
		n = (unsigned char)a;
	}
	else if (new->length[0] == 'h' && new->length[1] == '\0')
	{
		a = va_arg(ap, unsigned int);
		n = (unsigned short)a;
	}
	if (n == 0)
		new->f_hash = 0;
	str = ft_hex(n);
	if (new->conv_char == 'x')
		str = ft_string_tolower(str);
	return (ft_check_flags_diouxx(str, new));
}
