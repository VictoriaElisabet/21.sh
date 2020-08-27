/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 14:25:43 by vgrankul          #+#    #+#             */
/*   Updated: 2019/11/04 10:18:19 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char value;
	char *s1;

	value = (char)c;
	s1 = (char*)s;
	while (n)
	{
		if (*s1 == value)
		{
			return ((void*)s1);
		}
		n--;
		s1++;
	}
	return (NULL);
}
