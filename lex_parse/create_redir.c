/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <vgrankul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 11:28:19 by vgrankul          #+#    #+#             */
/*   Updated: 2020/09/16 15:17:52 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"
#include "../includes/sh.h"

void	get_io_num(t_token **head)
{
	t_token *tmp;
	int		len;

	if (*head != NULL)
	{
		tmp = *head;
		while (tmp->next != NULL)
			tmp = tmp->next;
		len = ft_strlen(tmp->token) - 1;
		if (tmp->token[len] == '-')
			len--;
		while (len > 0 && ft_isdigit(tmp->token[len]) == 1)
			len--;
		if (len == 0)
			tmp->type = IO_NUM;
	}
}

int		create_delim(char *command, char **delim, int *flags)
{
	int		i;

	i = 0;
	while (is_separator(command[i]) == 0 && command[i] != '\0')
	{
		if (command[i] == '\\')
		{
			*flags |= ESC;
			i++;
		}
		else if (command[i] == '\'')
			i = i + count_squoting_word(&command[i], flags);
		else if (command[i] == '"')
			i = i + count_dquoting_word(&command[i], flags);
		i++;
	}
	*delim = ft_strsub(command, 0, i);
	return (i);
}

int		create_heredoc(t_token **head, char *command, int *flags)
{
	char	*delim;
	char	*str;
	int		i;

	i = 0;
	while (is_word(command[i]) != 1 && command[i] != '\0')
		i++;
	i = i + create_delim(&command[i], &delim, flags);
	if (delim)
	{
		str = ft_hd_doc(delim);
		add_token(head, WORD, str, *flags);
		free(delim);
		free(str);
	}
	return (i);
}

int		create_redir(t_token **head, char *command, int flags)
{
	char	*tmp;
	int		i;

	tmp = NULL;
	i = 0;
	if (is_redir(command[i]) == 1)
	{
		i++;
		get_io_num(head);
		if (command[i] == '>' || command[i] == '<' || command[i] == '|' ||
		command[i] == '&')
		{
			i++;
			if (command[i++] == '-')
				i++;
		}
		if ((tmp = ft_strsub(command, 0, i)))
			add_token(head, REDIR, tmp, flags);
		if ((ft_strcmp(tmp, "<<") == 0 || ft_strcmp(tmp, "<<-") == 0) &&
		is_part_op(command[i]) != 1)
			i = i + create_heredoc(head, &command[i], &flags);
	}
	free(tmp);
	return (i);
}
