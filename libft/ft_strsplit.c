/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 15:39:39 by vgrankul          #+#    #+#             */
/*   Updated: 2019/11/04 16:45:51 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	wordlength(const char *str, char c)
{
	int i;

	i = 0;
	while (str[i] != c && str[i])
		i++;
	return (i);
}

static	int	get_word(const char *str, char c)
{
	int i;
	int word;

	i = 0;
	word = 0;
	if (str[i] != c)
		word++;
	while (str[i])
	{
		if (str[i] == c && str[i + 1] != c && str[i + 1] != '\0')
			word++;
		i++;
	}
	return (word);
}

char		**ft_strsplit(char const *s, char c)
{
	int		i;
	int		j;
	char	**arr;
	int		words;

	i = 0;
	j = 0;
	words = get_word((char*)s, c);
	arr = (char**)malloc(sizeof(char*) * (words + 1));
	if (arr)
	{
		while (i < words)
		{
			while (s[j] == c)
				j++;
			arr[i] = ft_strsub(&s[j], 0, wordlength(&s[j], c));
			j = j + wordlength(&s[j], c);
			i++;
		}
		arr[i] = NULL;
		return (arr);
	}
	return (NULL);
}
