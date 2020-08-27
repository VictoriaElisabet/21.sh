/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 16:05:09 by vgrankul          #+#    #+#             */
/*   Updated: 2019/11/07 16:05:13 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char value;
	unsigned char *s1;
	unsigned char *s2;

	value = (unsigned char)c;
	s1 = (unsigned char*)dst;
	s2 = (unsigned char*)src;
	while (n)
	{
		*s1 = *s2;
		if (*s2 == value)
		{
			*s1 = *s2;
			s1++;
			return ((void*)s1);
		}
		s1++;
		s2++;
		n--;
	}
	return (NULL);
}
