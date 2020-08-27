/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 11:58:34 by vgrankul          #+#    #+#             */
/*   Updated: 2019/11/04 15:29:14 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char value;
	char *str;

	value = (char)c;
	str = (char*)s;
	if (value == '\0')
		return (&str[ft_strlen(str)]);
	while (*str != '\0')
	{
		if (*str == value)
		{
			return (str);
		}
		str++;
	}
	return (NULL);
}
