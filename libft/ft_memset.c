/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 10:24:27 by vgrankul          #+#    #+#             */
/*   Updated: 2019/11/07 15:48:15 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	value;
	unsigned char	*str;
	size_t			i;

	value = (unsigned char)c;
	str = (unsigned char*)b;
	i = 0;
	while (i < len)
	{
		*str = value;
		i++;
		str++;
	}
	return (b);
}
