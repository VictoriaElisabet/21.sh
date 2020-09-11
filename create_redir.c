/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 11:28:19 by vgrankul          #+#    #+#             */
/*   Updated: 2019/10/31 13:49:20 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		get_IO_num(t_token **head)
{
	t_token *tmp;
	int		i;

	tmp = *head;
	i = 0;
	while (tmp->next != NULL)
		tmp = tmp->next;
	while(tmp->token[i] != '\0')
	{
		if (ft_isdigit(tmp->token[i]) == 0)
			return ;
		i++;
	}
	tmp->type = IO_NUM;
}

int			create_heredoc_word(char *command, char *delim, char **doc)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (command[i] != '\0')
	{
		j = 0;
		while (command[i + j] == delim[j] && delim[j] != '\0'
				&& command[i + j] != '\0')
			j++;
		if (delim[j] == '\0')
		{
			*doc = ft_strsub(command, 0, i);
			break ;
		}
		i++;
	}
	//om int e hittas borde kanske -1 returnas och men he bord ju hittas..
	return (i);
}
int			create_delim(char *command, char **delim, int *flags)
{
	int i;

	i = 0;
	while(command[i] != '\0' && command[i] != 't') // ska ju vara \n å int t
		i++;
	*delim = ft_strsub(command, 0, i);
	if (str_chr(*delim, '"') == 1)
		*flags |= DQ;
	if(str_chr(*delim, '\'') == 1)
		*flags |= SQ;
	return (i + 1);
}

int			create_heredoc(t_token **head, char *command, char **doc)
{
	char 	*delim;
	int		i;
	int		j;
	int		flags;

	i = 0;
	j = 0;
	flags = 0;
	i = i + create_delim(command, &delim, &flags);
	i = i + create_heredoc_word(&command[i], delim, doc);
	while(command[i] != '\0' && command[i] == delim[j])
	{
		i++;
		j++;
	}
	add_token(head, WORD, *doc, flags);
	free(delim);
	free(*doc);
	return(i);
}

int 		create_redir(t_token **head, char *command)
{
	int		i;
	char	*tmp;
	char	*doc;
	int		flags;

	i = 0;
	tmp = NULL;
	doc = NULL;
	flags = 0;
	if(is_redir(command[i]) == 1) 
	{
		i++;
		get_IO_num(head);
		if(command[i] == '>' || command[i] == '<' || command[i] == '|' || command[i] == '&')
		{
			i++;
			if(command[i] == '-')
				i++;
		}
		tmp = ft_strsub(command, 0, i);
		add_token(head, REDIR, tmp, flags);
		if (ft_strcmp(tmp, "<<") == 0 || ft_strcmp(tmp, "<<-") == 0)
			i = i + create_heredoc(head, &command[i], &doc);
	}
	free(tmp);
	return (i);
}