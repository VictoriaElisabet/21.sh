/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 11:05:46 by vgrankul          #+#    #+#             */
/*   Updated: 2019/11/07 14:48:43 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	int		i;
	int		len;

	i = 0;
	len = (ft_strlen((char*)s1) + ft_strlen((char*)s2));
	new = (char*)malloc(sizeof(char) * (len + 1));
	if (new)
	{
		while (*s1 != '\0')
		{
			new[i++] = *s1++;
		}
		while (*s2 != '\0')
		{
			new[i++] = *s2++;
		}
		new[i] = '\0';
		return (new);
	}
	else
		return (NULL);
}
