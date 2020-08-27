/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <vgrankul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 14:07:26 by vgrankul          #+#    #+#             */
/*   Updated: 2020/02/25 11:59:23 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_set_length(const char *format, t_format_struct *new)
{
	int j;
	int i;

	j = 0;
	i = 0;
	while (ft_isalpha(format[i]) == 1 && format[i] != '.' &&
			ft_is_conv_char(format[i]) != 1 && j < 2 && format[i] != '\0')
	{
		new->length[j] = format[i];
		j++;
		i++;
	}
	new->length[j] = '\0';
	return (i);
}

int		ft_set_precision(const char *format, t_format_struct *new, va_list ap)
{
	int i;

	i = 0;
	new->prec = 1;
	if (format[i] == '*')
		new->precision = check_asterisk(ap);
	while (ft_isdigit(format[i]) == 1 && format[i] != '\0')
		new->precision = new->precision * 10 + format[i++] - 48;
	return (i);
}

void	fill_struct(const char *format, t_format_struct *new, int i, va_list ap)
{
	while (format[i] != '\0' && ft_is_conv_char(format[i]) != 1)
	{
		if (ft_is_flag(format[i]) == 1)
			ft_set_flag(format[i], new);
		if (format[i] == '*')
			new->width = check_asterisk(ap);
		if (ft_isdigit(format[i]) == 1 && format[i] != '0')
		{
			while (ft_isdigit(format[i]) == 1 && format[i] != '\0')
				new->width = new->width * 10 + format[i++] - 48;
		}
		if (format[i] == '.')
		{
			i++;
			i = i + ft_set_precision(&format[i], new, ap);
		}
		if (ft_isalpha(format[i]) == 1 &&
			format[i] != '.' && ft_is_conv_char(format[i]) != 1)
			i = i + ft_set_length(&format[i], new);
		if (ft_is_conv_char(format[i]) == 1 || format[i] == '%')
			break ;
		i++;
	}
	if (ft_is_conv_char(format[i]) == 1 || format[i] == '%')
		new->conv_char = format[i];
}

int		create_struct(const char *format, va_list ap)
{
	int				i;
	t_format_struct new;

	i = 0;
	ft_set_to_zero(&new);
	fill_struct(format, &new, i, ap);
	if (ft_is_conv_char(new.conv_char) == 1 || new.conv_char == '%')
		return (ft_check_conv_char(&new, ap));
	else
		return (0);
}
