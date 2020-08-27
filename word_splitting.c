/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_splitting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 11:28:19 by vgrankul          #+#    #+#             */
/*   Updated: 2019/10/31 13:49:20 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_separator(int c)
{
	if (c == ' ' || c == '\t' || c == '|' || c == '&' || c == ';' || c == '\n')
		return (1);
	return (0);
}

int		count_quoting_word(char *command)
{
	int i;

	i = 0;
	if (command[i] == '"' || command[i] == '\'')
		i++;
	while (command[i] != '"' && command[i] != '\'' && command[i] != '\0'
	&& is_separator(command[i]) != 1)
		i++;
	if (is_separator(command[i]) == 1)
		i = i - 1;
	return (i);
}

int		count_words(char *command, int count)
{
	int i;

	i = 0;
	while (command[i] != '\0')
	{
		if (is_separator(command[i]) == 0)
		{
			count++;
			while (is_separator(command[i]) == 0 && command[i] != '\0')
			{
				if (command[i] == '"' || command[i] == '\'')
					i = i + count_quoting_word(&command[i]);
				i++;
			}
		}
		if (command[i] == '|' || command[i] == '&' || command[i] == ';' ||
		command[i] == '\n')
		{
			if (command[i + 1] == '|' || command[i + 1] == '&')
				i++;
			count++;
		}
		i++;
	}
	return (count);
}

int		count_wordlen(char *command)
{
	int i;

	i = 0;
	if (command[0] == '|' || command[0] == '&' || command[0] == ';' ||
	command[0] == '\n')
	{
		i++;
		if (command[i] == '|' || command[i] == '&')
			i++;
		return (i);
	}
	while (is_separator(command[i]) == 0 && command[i] != '\0')
	{
		if (command[i] == '"' || command[i] == '\'')
			i = i + count_quoting_word(&command[i]);
		i++;
	}
	return (i);
}

char	**word_splitting(char *command, int count)
{
	char	**words;
	int		i;
	int		j;
	int		words_nbr;

	j = 0;
	i = 0;
	words_nbr = count_words(command, count);
	if (!(words = (char**)malloc(words_nbr * sizeof(char*) + 1)))
		return (NULL);
	while (j < words_nbr)
	{
		while ((command[i] == ' ' || command[i] == '\t') && command[i] != '\0')
			i++;
		if (!(words[j] = ft_strsub(&command[i], 0, count_wordlen(&command[i]))))
		{
			destroy_arr(words);
			return (NULL);
		}
		i = i + count_wordlen(&command[i]);
		j++;
	}
	words[j] = NULL;
	return (words);
}
