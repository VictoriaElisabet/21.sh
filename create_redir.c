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

	tmp = *head;
	while (tmp != NULL)
		tmp = tmp->next;
	if(ft_isdigit(ft_atoi(tmp->token)) == 1)
	{

		tmp->type = IO_NUM;
	}
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

int			create_heredoc(char *command, char **doc)
{
	char 	*delim;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while(command[i] != '\0' && command[i] != 't')
		i++;
	delim = ft_strsub(command, 0, i);
	i++;
	i = i + create_heredoc_word(&command[i], delim, doc);
	while(command[i] != '\0' && command[i] == delim[j])
	{
		i++;
		j++;
	}
	return(i);
}
int 		create_redir(t_token **head, char *command)
{
	int		i;
	char	*tmp;
	char	*doc;

	i = 0;
	tmp = NULL;
	doc = NULL;
	if(is_redir(command[i]) == 1) 
	{
		i++;
		//get_IO_num(head);
		if(command[i] == '>' || command[i] == '<' || command[i] == '|' || command[i] == '&')
		{
			i++;
			if(command[i] == '-')
				i++;
		}
		tmp = ft_strsub(command, 0, i);
		if (ft_strcmp(tmp, "<<") == 0 || ft_strcmp(tmp, "<<-") == 0)
			i = i + create_heredoc(&command[i], &doc);
		add_token(head, REDIR, tmp);
		add_token(head, WORD, doc);
	}
	return (i);
}