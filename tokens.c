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

int		str_chr(char *str, int c)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int		is_separator(int c)
{
	if (c == ' ' || c == '\t' || c == '|' || c == '&' || c == ';' || c == '\n' || c == '<' || c == '>')
		return (1);
	return (0);
}

int		is_part_op(int c)
{
	if (c == '|' || c == '&' || c == ';' || c == '\n')
		return (1);
	return (0);
}

int		is_redir(int c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

int		is_word(int c)
{
	if(ft_isprint(c) == 1 && is_separator(c) != 1)
		return (1);
	return (0);
}

void		set_type(char *tok_type, int *type_f)
{
	int		i;
	char	types[5][11] = {"WORD_ASSIGN", "WORD", "OPERATOR", "REDIR", "IO_NUM"};

	i = 0;
	while(i < 5)
	{
		if(ft_strcmp(types[i], tok_type) == 0)
			*type_f |= 1 << i;
		i++;
	}
}

void	destroy_tok_list(t_token *head)
{
	t_token *tmp;

	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp->token);
		free(tmp);
	}
}

void		print_token(t_token *head)
{
		t_token *tmp = head;
    while (tmp != NULL)
    {
        ft_printf("%s\n", tmp->token);
        tmp = tmp->next;
    }
}

t_token		*create_token(char *tok_type, char *tok)
{
	t_token *new;

	new = (t_token*)malloc(sizeof(t_token));
	new->token = ft_strdup(tok);
	free(tok);
	set_type(tok_type, &new->type);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void		add_token(t_token **head, char *tok_type, char *tok)
{
	t_token	*new;
	t_token *tmp;

	new = create_token(tok_type, tok);
	tmp = *head;
	if (*head == NULL)
	{
		new->prev = NULL;
		*head = new;
	}
	else
	{
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	tmp->prev = tmp;
	}
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
		{
			i = i + count_quoting_word(&command[i]);
		}
		i++;
	}
	tmp = ft_strsub(command, 0, i);
	if (str_chr(tmp, '=') == 1)
		add_token(head, "WORD_ASSIGN", tmp);
	else
		add_token(head, "WORD", tmp);
	return (i);
}

int			create_op(t_token **head, char *command)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	//ft_printf("str %s\n", command);
	if(is_redir(command[0]) == 1) 
	{
		i++;
		if(command[i] == '>' || command[i] == '<' || command[i] == '|' || command[i] == '&')
		{
			i++;
			if(command[i] == '-')
			{
				i++;
			}
		}
		tmp = ft_strsub(command, 0, i);	
		add_token(head, "REDIR", tmp);
	}
	else 
	{
		if(is_part_op(command[0]) == 1)
		{
			i++;
			if(command[i] == '|' || command[i] == '&' || command[i] == ';')
			{
				i++;
			}
			tmp = ft_strsub(command, 0, i);
			//ft_printf("ct to%s\n", tmp);
			add_token(head, "OPERATOR", tmp);
		}
	}

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
		if(is_part_op(command[i]) == 1 || is_redir(command[i]) == 1)
			i = i + create_op(&head, &command[i]);
		//else if (command[i] == '\n')
		//	ft_printf("hej");
		else if (is_word(command[i]) == 1)
			i = i + create_word(&head, &command[i]);
		
		else		//i = create word or ass word
			i++;
	}
		print_token(head);
							destroy_tok_list(head);
	return(head);
}