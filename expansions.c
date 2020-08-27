/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 11:28:19 by vgrankul          #+#    #+#             */
/*   Updated: 2019/10/31 13:49:20 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**remove_word(char **words, int word)
{
	int		i;
	int		j;
	char	**new;
	int		count;

	i = 0;
	j = 0;
	count = count_arr(words) - 1;
	if ((new = (char**)malloc((count * sizeof(char*) + 1))))
	{
		while (j < count)
		{
			if (i == word)
				i++;
			if (!(new[j] = ft_strdup(words[i])))
			{
				destroy_arr(new);
				return (NULL);
			}
			i++;
			j++;
		}
	}
	new[j] = NULL;
	return (new);
}

int		str_chr(char *str, int c)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	word_expansion(char ***words, char **env)
{
	int		i;
	char	**tmp;

	i = 0;
	while ((*words)[i] != NULL)
	{
		if (str_chr((*words)[i], '\'') != 1)
		{
			if (str_chr((*words)[i], '"') != 1)
				(*words)[i] = tilde_expansion((*words)[i], env);
			if (ft_strcmp(((*words)[i] =
			parameter_expansion((*words)[i], env)), "\0") == 0)
			{
				if ((tmp = remove_word((*words), i)))
				{
					destroy_arr((*words));
					(*words) = tmp;
				}
				i--;
			}
		}
		i++;
	}
}
