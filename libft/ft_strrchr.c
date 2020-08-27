/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <vgrankul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 12:42:19 by vgrankul          #+#    #+#             */
/*   Updated: 2020/02/10 16:17:50 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	char	value;
	int		len;

	str = (char*)s;
	value = (char)c;
	len = ft_strlen(str);
	if (value == '\0')
		return (&str[ft_strlen(str)]);
	while (len > 0)
	{
		if (str[len - 1] == value)
		{
			return (&str[len - 1]);
		}
		len--;
	}
	return (NULL);
}
