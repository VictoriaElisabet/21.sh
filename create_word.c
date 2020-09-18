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

#include "./includes/minishell.h"

void	remove_squotes(char **token)
{
	int i;
	char *new;

	i = 1;
	while ((*token)[i] != '\0' && (*token)[i] != '\'')
	{
		if ((*token)[i] == '\\')
			i++;
		i++;
	}
	new = ft_strsub(*token, 1, i - 1);
	free(*token);
	(*token) = new;
}

void	remove_dquotes(char **token)
{
	int i;
	char *new;

	i = 1;
	while ((*token)[i] != '\0' && (*token)[i] != '"')
	{
		if ((*token)[i] == '\\')
			i++;
		i++;
	}
	new = ft_strsub(*token, 1, i - 1);
	free(*token);
	(*token) = new;
}

void	remove_backslash(char **token)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = ft_strnew(ft_strlen(*token) - 1);
	while ((*token)[i] != '\0')
	{
		if ((*token)[i] != '\\')
		{
			new[j] = (*token)[i];
			j++;
		}
		i++;
	}
	new[j] = '\0';
	free(*token);
	(*token) = new;
}

void	remove_quoting(t_token **head)
{
	t_token *tmp;

	tmp = *head;
	while(tmp != NULL)
	{
		if (tmp->type == WORD)
		{
			if (tmp->flags & SQ)
				remove_squotes(&tmp->token);
			if (tmp->flags & DQ)
				remove_dquotes(&tmp->token);
			if (tmp->flags & ESC)
				remove_backslash(&tmp->token);
		}
		tmp = tmp->next;
	}
}

int		is_separator(int c)
{
	if (c == ' ' || c == '\t' || c == '|' || c == '&' ||
		c == ';' || c == '\n' || c == '<' || c == '>')
		return (1);
	return (0);
}

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
	while(tmp->next != NULL)
		tmp = tmp->next;
	if (tmp->type != WORD)
		return(1);
	return(0);
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
		if (command[i] == '\'')
			i = i + count_squoting_word(&command[i], &flags);
		if (command[i] == '"')
			i = i + count_dquoting_word(&command[i], &flags);
		i++;
	}
	if ((tmp = ft_strsub(command, 0, i)))
	{
		if (str_chr(tmp, '=') == 1 && check_prev_word(head) == 1)
			add_token(head, WORD_ASSIGN, tmp, flags);
		else
			add_token(head, WORD, tmp, flags);
		free(tmp);
	}
	return (i);
}
