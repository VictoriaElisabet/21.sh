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

#include "./includes/21sh.h"

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

int		create_heredoc_word(char *command, int i, char *delim, char **doc,
int flags)
{
	//int		i;
	int		j;
	int		k;

	//i = 0;
	j = 0;
	k = 0;
	while (command[i] != '\n')
		i++;
	i++;
	//ft_printf("efter i %s", &command[i]);
	while (command[k + i] != '\0' && command[k + i] != EOF)
	{
		j = 0;
		while (command[(k + i) + j] == delim[j] && delim[j] != '\0'
				&& command[(k + i) + j] != '\0' && command[(k + i) + j] != EOF)
			j++;
		if (delim[j] == '\0')
			break ;
		k++;
	}
	//ft_printf("k = %d", k);
	if (!(*doc = ft_strsub(command, i, k)))
		*doc = NULL;
	ft_printf("doc %s stop\n", *doc);
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

int		create_delim(char *command, int i, char **delim, int *flags)
{
	int j;

	j = 0;
	//ft_printf("delimstr %s \n", &command[i]);
	while (is_separator(command[i + j]) == 0 && command[i + j] != '\0' &&
	command[i + j] != '\n')
	{
		if (command[i + j] == '\\')
		{
			*flags |= ESC;
			j++;
		}
		else if (command[i + j] == '\'')
			j = j + count_squoting_word(&command[i + j], flags);
		else if (command[i + j] == '"')
			j = j + count_dquoting_word(&command[i + j], flags);
		j++;
	}
	*delim = ft_strsub(command, i, j);
	delim_quotes(delim, *flags);
	return (j);
}

int		create_heredoc(t_token **head, int i, char **doc, char **comm)
{
	char	*delim;
	int		flags;
	char	*tmp;
	int		j;

	flags = 0;
	j = 0;
	// remove tabs if <<-
	ft_printf("COMMAND %s %d\n", (*comm), i);
	while ((*comm)[i + j] != '\0' && is_word((*comm)[i + j]) != 1)
		j++;
	j = j + create_delim((*comm), i, &delim, &flags);
	ft_printf("delim%s stop\n", delim);
	if (delim && ft_strlen(delim) != 0)
	{
		//create_heredoc_word(&command[i], command, delim, doc, flags);
		tmp = ft_strsub((*comm), 0, create_heredoc_word((*comm), i + j, delim, doc, flags));
		free((*comm));
		(*comm) = tmp;
		ft_printf("comm %sstop", (*comm));
		if (*doc)
		{
			add_token(head, WORD, *doc, flags);
			free(*doc);
		}
		//if (command[i] == '\0')
		//	add_token(head, OPERATOR, "\n", 0);
		//free(delim);
	}
	else
	{
		free(delim);
		print_redir_error(SYNTAX_ERR);
		return (0);
	}
	free(delim);
	//ft_printf("jjj %d\n", j);
	return (j);
}

int		create_redir(t_token **head, char **command, int i)
{
	char	*tmp;
	char	*doc;
	int		flags;
	int		j;

	tmp = NULL;
	doc = NULL;
	flags = 0;
	j = 0;
	if (is_redir((*command)[i + j]) == 1)
	{
		j++;
		get_io_num(head);
		if ((*command)[i + j] == '>' || (*command)[i + j] == '<' || (*command)[i + j] == '|' ||
		(*command)[i + j] == '&')
		{
			j++;
			if ((*command)[i + j] == '-')
				j++;
		}
		if ((tmp = ft_strsub(&(*command)[i], 0, j)))
			add_token(head, REDIR, tmp, flags);
		if (ft_strcmp(tmp, "<<") == 0 || ft_strcmp(tmp, "<<-") == 0)
			j = j + create_heredoc(head, i + j, &doc, command);
	}
	free(tmp);
	//ft_printf(" j%d\n", j);
	return (j);
}
