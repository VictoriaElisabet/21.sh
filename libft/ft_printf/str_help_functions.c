/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_help_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <vgrankul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 14:07:26 by vgrankul          #+#    #+#             */
/*   Updated: 2020/02/24 14:49:23 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		count_to_dot(char *str)
{
	int counter;

	counter = 0;
	while (*str != '\0' && *str != '.')
	{
		str++;
		counter++;
	}
	return (counter + 1);
}

char	*ft_copy_string(char *str, int len)
{
	char	*str1;
	int		i;

	i = 0;
	str1 = (char*)malloc(len * sizeof(char) + 1);
	while (i < len && str[i] != '\0')
	{
		str1[i] = str[i];
		i++;
	}
	str1[i] = '\0';
	return (str1);
}

char	*ft_copy_string_float(char *str, t_format_struct *new, int dotlen)
{
	char	*str1;
	int		i;
	int		j;
	int		strlen;

	i = 0;
	j = 0;
	strlen = count_to_dot(str) + new->precision;
	str1 = (char*)malloc(strlen * sizeof(char) + 1);
	while (str[i] != '\0' && i < strlen)
	{
		if (dotlen > 0)
		{
			str1[j++] = str[i];
			dotlen--;
		}
		else if (dotlen == 0 && new->precision > 0)
		{
			str1[j++] = str[i];
			new->precision--;
		}
		i++;
	}
	str1[i] = '\0';
	return (str1);
}

int		format_strlen(const char *format)
{
	int i;

	i = 0;
	while (format[i] != '\0' && ft_is_conv_char(format[i]) != 1)
	{
		if (format[i] == '%')
			break ;
		i++;
	}
	return (i);
}
