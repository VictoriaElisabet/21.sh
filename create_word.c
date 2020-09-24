/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <vgrankul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 11:28:19 by vgrankul          #+#    #+#             */
/*   Updated: 2020/09/16 15:17:34 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/21sh.h"

int		count_squoting_word(char *command, int *flags)
{
	int i;

	i = 0;
	*flags |= SQ;
	if (command[i] == '\'')
		i++;
	while (command[i] != '\'' && command[i] != '\0')
	{
		if (command[i] == '\\')
		{
			*flags |= ESC;
			i++;
		}
		i++;
	}
	if (is_separator(command[i]) == 1)
		i = i - 1;
	return (i);
}

int		count_dquoting_word(char *command, int *flags)
{
	int i;

	i = 0;
	*flags |= DQ;
	if (command[i] == '"')
		i++;
	while (command[i] != '"' && command[i] != '\0')
	{
		if (command[i] == '\\')
		{
			*flags |= ESC;
			i++;
		}
		i++;
	}
	if (is_separator(command[i]) == 1)
		i = i - 1;
	return (i);
}

int		check_prev_word(t_token **head)
{
	t_token *tmp;

	tmp = *head;
	while (tmp->next != NULL)
		tmp = tmp->next;
	if (tmp->type != WORD)
		return (1);
	return (0);
}

void	add_word(t_token **head, char *tmp, int flags)
{
	if (str_chr(tmp, '=') == 1 && check_prev_word(head) == 1)
		add_token(head, WORD_ASSIGN, tmp, flags);
	else
		add_token(head, WORD, tmp, flags);
	free(tmp);
}

int		create_word(t_token **head, char *command)
{
	int		i;
	char	*tmp;
	int		flags;

	i = 0;
	tmp = NULL;
	flags = 0;
	while (is_separator(command[i]) == 0 && command[i] != '\0')
	{
		if (command[i] == '\\')
		{
			flags |= ESC;
			i++;
		}
		else if (command[i] == '\'')
			i = i + count_squoting_word(&command[i], &flags);
		else if (command[i] == '"')
			i = i + count_dquoting_word(&command[i], &flags);
		i++;
	}
	if ((tmp = ft_strsub(command, 0, i)))
		add_word(head, tmp, flags);
	return (i);
}
