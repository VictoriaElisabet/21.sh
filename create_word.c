/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_word.c                                      :+:      :+:    :+:   */
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
	if (c == ' ' || c == '\t' || c == '|' || c == '&' || c == ';' || c == '\n' || c == '<' || c == '>')
		return (1);
	return (0);
}

int		count_quoting_word(char *command)
{
	int i;

	i = 0;
	if (command[i] == '"' || command[i] == '\'')
		i++;
	while (command[i] != '"' && command[i] != '\'' && command[i] != '\0')
		i++;
	if (is_separator(command[i]) == 1)
		i = i - 1;
	return (i);
}

int			create_word(t_token **head, char *command)
{
	int i;
	char *tmp;

	i = 0;
	tmp = NULL;
	while (is_separator(command[i]) == 0 && command[i] != '\0')
	{
		if (command[i] == '"' || command[i] == '\'')
			i = i + count_quoting_word(&command[i]);
		i++;
	}
	tmp = ft_strsub(command, 0, i);
	if (str_chr(tmp, '=') == 1)
		add_token(head, WORD_ASSIGN, tmp);
	else
		add_token(head, WORD, tmp);
	return (i);
}