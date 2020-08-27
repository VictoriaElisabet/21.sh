/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <vgrankul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 14:07:26 by vgrankul          #+#    #+#             */
/*   Updated: 2020/02/25 11:51:02 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_add_zero_diouxx(char *str, int len, int preclen)
{
	char	*str2;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!(str2 = (char*)malloc(len * sizeof(char) + 1)))
		return (NULL);
	while (j < len)
	{
		if (preclen == 0)
			str2[j] = str[i++];
		if (str[i] == '-' || str[i] == '+')
			str2[j++] = str[i++];
		if (preclen > 0)
		{
			str2[j] = '0';
			preclen--;
		}
		j++;
	}
	str2[j] = '\0';
	return (str2);
}

char	*ft_set_space_right(char *str, char *str2,
	t_format_struct *new, char sign)
{
	int i;
	int j;
	int widthlen;

	i = 0;
	j = 0;
	widthlen = new->width - ft_strlen(str);
	while ((new->conv_char == 'x' || new->conv_char == 'X') &&
				new->f_hash == 1 && sign == '0' && j < 2)
		str2[j++] = str[i++];
	while (j < (int)((new->width - ft_strlen(str)) + ft_strlen(str)))
	{
		if (widthlen == 0)
			str2[j++] = str[i++];
		if (((str[i] == '-' || str[i] == '+' || str[i] == ' ') && sign == '0')
		|| (str[i] == '-' && sign == '0' && new->conv_char == 'f'))
			str2[j++] = str[i++];
		if (widthlen > 0)
		{
			str2[j++] = sign;
			widthlen--;
		}
	}
	str2[j] = '\0';
	return (str2);
}

char	*ft_set_space_left(char *str, char *str2, char sign, int widthlen)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		str2[j] = str[i];
		i++;
		j++;
	}
	while (widthlen > 0)
	{
		str2[j] = sign;
		widthlen--;
		j++;
	}
	str2[j] = '\0';
	return (str2);
}

char	*ft_set_space(char *str, t_format_struct *new, char sign)
{
	char	*str2;
	int		len;
	int		widthlen;

	len = (new->width - ft_strlen(str)) + ft_strlen(str);
	widthlen = new->width - ft_strlen(str);
	if (!(str2 = (char*)malloc(len * sizeof(char) + 1)))
		return (NULL);
	if (new->f_minus == 1 && new->f_zero != 1)
		str2 = ft_set_space_left(str, str2, sign, widthlen);
	else
		str2 = ft_set_space_right(str, str2, new, sign);
	return (str2);
}

char	*ft_add_zero_float(char *str, int len, int dotlen, int i)
{
	char	*str2;
	int		strlen;
	int		j;

	j = 0;
	strlen = ft_strlen(str) + len;
	if (!(str2 = (char*)malloc(strlen * sizeof(char) + 1)))
		return (NULL);
	while (str[i] != '\0')
	{
		if (dotlen > 0)
		{
			str2[j++] = str[i++];
			dotlen--;
		}
		else if (len > 0 && dotlen == 0)
		{
			str2[j++] = '0';
			len--;
		}
		else if (dotlen == 0 && len == 0)
			str2[j++] = str[i++];
	}
	str2[j] = '\0';
	return (str2);
}
