/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 10:22:41 by vgrankul          #+#    #+#             */
/*   Updated: 2019/11/04 12:58:51 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char *new;
	char *ptr;

	if (!s)
		return (NULL);
	new = (char*)malloc(sizeof(char) * ft_strlen((char*)s) + 1);
	ptr = new;
	if (new)
	{
		while (*s != '\0')
		{
			*new = f(*s);
			new++;
			s++;
		}
		*new = '\0';
		return (ptr);
	}
	return (NULL);
}
