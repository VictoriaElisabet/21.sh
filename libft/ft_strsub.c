/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 11:48:19 by vgrankul          #+#    #+#             */
/*   Updated: 2019/10/30 12:49:44 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char *str;
	char *ptr;

	str = (char*)malloc((sizeof(char) * len) + 1);
	ptr = str;
	if (str)
	{
		while (len && *s != '\0')
		{
			*str = (char)s[start];
			str++;
			start++;
			len--;
		}
		*str = '\0';
		return (ptr);
	}
	else
		return (NULL);
}
