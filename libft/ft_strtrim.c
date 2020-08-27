/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 13:23:55 by vgrankul          #+#    #+#             */
/*   Updated: 2019/11/05 14:33:34 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		is_whitespace(char c)
{
	return (c == ' ' || c == '\n' || c == '\t');
}

char			*ft_strtrim(char const *s)
{
	int		i;
	int		j;
	int		k;
	char	*str;

	i = 0;
	k = 0;
	if (!s)
		return (NULL);
	while (is_whitespace(s[i]) && s[i] != '\0')
		i++;
	j = ft_strlen((char*)s);
	while (i < j && is_whitespace(s[j - 1]))
		j--;
	if (j == i)
		return (ft_strnew(1));
	if (!(str = (char*)malloc(sizeof(char) * (j - i) + 1)))
		return (NULL);
	while (i < j)
		str[k++] = (char)s[i++];
	str[k] = '\0';
	return (str);
}
