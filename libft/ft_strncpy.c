/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 14:29:08 by vgrankul          #+#    #+#             */
/*   Updated: 2019/11/04 15:08:57 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t	i;
	char	*ptr;

	ptr = dst;
	i = 0;
	while (i < len && *src != '\0')
	{
		*dst = *src;
		dst++;
		src++;
		i++;
	}
	while (i < len)
	{
		*dst = '\0';
		i++;
		dst++;
	}
	return (ptr);
}
