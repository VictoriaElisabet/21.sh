/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 11:28:19 by vgrankul          #+#    #+#             */
/*   Updated: 2019/10/31 13:49:20 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			is_part_op(int c)
{
	if (c == '|' || c == '&' || c == ';' || c == '\n')
		return (1);
	return (0);
}

int			is_redir(int c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

int			is_word(int c)
{
	if (ft_isprint(c) == 1 && is_separator(c) != 1)
		return (1);
	return (0);
}

int			create_op(t_token **head, char *command)
{
	int		i;
	char	*tmp;
	int		flags;

	i = 0;
	tmp = NULL;
	flags = 0;
	if (is_part_op(command[i]) == 1)
	{
		i++;
		if (command[i] == '|' || command[i] == '&' || command[i] == ';')
			i++;
		if ((tmp = ft_strsub(command, 0, i)))
			add_token(head, OPERATOR, tmp, flags);
	}
	free(tmp);
	return (i);
}

t_token		*create_tokens(char *command)
{
	t_token		*head;
	int			i;

	head = NULL;
	i = 0;
	while (command[i] != '\0')
	{
		// if i -1 isnt backslash
		if (is_part_op(command[i]) == 1)
			i = i + create_op(&head, &command[i]);
		else if (is_redir(command[i]) == 1)
			i = i + create_redir(&head, &command[i]);
		//else if (command[i] == '\n')
		else if (is_word(command[i]) == 1)
			i = i + create_word(&head, &command[i]);
		else
			i++;
	}
	return (head);
}
