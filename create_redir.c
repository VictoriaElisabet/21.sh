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

#include "./includes/minishell.h"

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

void	add_quotes(char **doc, int flags)
{
	int		c;
	int		j;
	int		i;
	char	*new;

	c = flags & SQ ? '\'' : '"';
	i = 0;
	j = 0;
	new = ft_strnew(ft_strlen(*doc) + 2);
	new[i++] = c;
	while ((*doc)[j] != '\0')
	{
		new[i] = (*doc)[j];
		j++;
		i++;
	}
	new[i++] = c;
	new[i] = '\0';
	free(*doc);
	(*doc) = new;
}

void	rem_delim_quotes(char **delim, int flags, int sindex)
{
	int		i;
	int		j;
	int		eindex;
	char	*new;

	i = 0;
	j = 0;
	new = ft_strnew(ft_strlen(*delim) - 2);
	eindex = get_quote_index(*delim, flags);
	while ((*delim)[i] != '\0')
	{
		if (i != sindex && i != eindex)
		{
			new[j] = (*delim)[i];
			j++;
		}
		i++;
	}
	new[j] = '\0';
	free(*delim);
	(*delim) = new;
}

int		create_heredoc_word(char *command, char *delim, char **doc,
int flags)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (command[i] != '\0' && command[i] != EOF)
	{
		j = 0;
		if (command[i] == '\n' && command[i + 1] == '\0')
			break ;
		while (command[i + j] == delim[j] && delim[j] != '\0'
				&& command[i + j] != '\0' && command[i + j] != EOF)
			j++;
		if (delim[j] == '\0')
			break ;
		i++;
	}
	if (!(*doc = ft_strsub(command, 0, i)))
		*doc = NULL;
	if ((flags & SQ || flags & DQ) && *doc != NULL)
		add_quotes(doc, flags);
	return (i);
}

void	delim_quotes(char **delim, int flags)
{
	int i;

	i = 0;
	while ((*delim)[i] != '\0')
	{
		if (flags & DQ && (*delim)[i] == '"')
			rem_delim_quotes(delim, flags, i);
		if (flags & SQ && (*delim)[i] == '\'')
			rem_delim_quotes(delim, flags, i);
		i++;
	}
}

int		create_delim(char *command, char **delim, int *flags)
{
	int		i;

	i = 0;
	while (is_separator(command[i]) == 0 && command[i] != '\0' &&
	command[i] != '\n')
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
	delim_quotes(delim, *flags);
	return (i + 1);
}

int		create_heredoc(t_token **head, char *command, char **doc)
{
	char	*delim;
	int		i;
	int		flags;

	i = 0;
	flags = 0;
	// remove tabs if <<-
	while (command[i] != '\0' && is_word(command[i]) != 1)
		i++;
	i = i + create_delim(&command[i], &delim, &flags);
	if (delim && ft_strlen(delim) != 0)
	{
		i = i + create_heredoc_word(&command[i], delim, doc, flags);
		i = i + ft_strlen(delim);
		if (*doc)
			add_token(head, WORD, *doc, flags);
		if (command[i] == '\0')
			add_token(head, OPERATOR, "\n", 0);
		free(delim);
		free(*doc);
	}
	else
		print_redir_error(SYNTAX_ERR);
	return (i);
}

int		create_redir(t_token **head, char *command)
{
	int		i;
	char	*tmp;
	char	*doc;
	int		flags;

	i = 0;
	tmp = NULL;
	doc = NULL;
	flags = 0;
	if (is_redir(command[i]) == 1)
	{
		i++;
		get_io_num(head);
		if (command[i] == '>' || command[i] == '<' || command[i] == '|' ||
		command[i] == '&')
		{
			i++;
			if (command[i] == '-')
				i++;
		}
		if ((tmp = ft_strsub(command, 0, i)))
			add_token(head, REDIR, tmp, flags);
		if (ft_strcmp(tmp, "<<") == 0 || ft_strcmp(tmp, "<<-") == 0)
			i = i + create_heredoc(head, &command[i], &doc);
	}
	free(tmp);
	return (i);
}
