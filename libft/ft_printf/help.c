/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <vgrankul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 12:52:28 by vgrankul          #+#    #+#             */
/*   Updated: 2020/02/24 17:04:10 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		set_len(long long first, long long second, long double nb)
{
	int len;

	if (second == 0)
		len = ft_count_digits(first, 10) + ft_count_digits(second, 10) + 7;
	else if (nb < 0)
		len = ft_count_digits(first, 10) + ft_count_digits(second, 10) + 3;
	else
		len = ft_count_digits(first, 10) + ft_count_digits(second, 10) + 2;
	return (len);
}

char	*ft_add_ox(char *str, t_format_struct *new)
{
	char *str1;
	char *tmp;

	tmp = str;
	if (!(str1 = (char*)malloc(3 * sizeof(char))))
		return (NULL);
	if (new->conv_char == 'X')
	{
		str1[0] = '0';
		str1[1] = 'X';
		str1[2] = '\0';
	}
	else
	{
		str1[0] = '0';
		str1[1] = 'x';
		str1[2] = '\0';
	}
	str = ft_strjoin(str1, str);
	free(str1);
	free(tmp);
	return (str);
}

char	*ft_set_sign(char *str, char sign)
{
	char *str1;
	char *tmp;

	tmp = str;
	str1 = (char*)malloc(2 * sizeof(char));
	if (str[0] == '-')
		return (str);
	str1[0] = sign;
	str1[1] = '\0';
	str = ft_strjoin(str1, str);
	free(str1);
	free(tmp);
	return (str);
}

int		check_asterisk(va_list ap)
{
	long long n;

	n = va_arg(ap, int);
	if (n < 0)
		return (0);
	else
		return (n);
}
