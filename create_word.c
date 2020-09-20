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

void	remove_esc_sign(char **token, int index)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = ft_strnew(ft_strlen(*token) - 1);
	while ((*token)[i] != '\0')
	{
		if (i != index)
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

void	remove_esc(t_token **tokens)
{
	int	i;
	int flags;

	i = 0;
	flags = 0;
	while ((*tokens)->token[i] != '\0')
	{
		if ((*tokens)->flags & SQ && (*tokens)->token[i] == '\'')
			i = i + count_squoting_word(&(*tokens)->token[i], &flags);
		else if ((*tokens)->flags & DQ && (*tokens)->token[i] == '"')
		{
			
			i = i + count_dquoting_word(&(*tokens)->token[i], &flags);
		}
		else if ((*tokens)->token[i] == '\\')
			remove_esc_sign(&(*tokens)->token, i);
		i++;
	}
}

int		get_quote_index(char *token, int flags)
{
	int len;
	int c;

	len = ft_strlen(token);
	c = (flags & SQ) ? '\'' : '"';
	while(len > 0)
	{
		if(token[len] == c)
			return(len);
		len--;
	}
	return (-1);
}

void	remove_squotes(t_token **tokens, int sindex)
{
	int		i;
	int		j;
	int		eindex;
	char	*new;

	i = 0;
	j = 0;
	new = ft_strnew(ft_strlen((*tokens)->token) - 2);
	eindex = get_quote_index((*tokens)->token, (*tokens)->flags);
	while ((*tokens)->token[i] != '\0')
	{
		if (i != sindex && i != eindex)
		{
			new[j] = (*tokens)->token[i];
			j++;
		}
		
		//if ((*token)[i] == '\\')
		//	i++;
		i++;
	}~~
	new[j] = '\0';
	(*tokens)->flags &= ~SQ;
	free((*tokens)->token);
	(*tokens)->token = new;
}

void	remove_dquotes(t_token **tokens, int sindex)
{
	int		i;
	int		j;
	int		eindex;
	char	*new;

	i = 0;
	j = 0;
	new = ft_strnew(ft_strlen((*tokens)->token) - 2);
	eindex = get_quote_index((*tokens)->token, (*tokens)->flags);
	while ((*tokens)->token[i] != '\0')
	{
		/*if ((*tokens)->token[i] == '\\' && ((*tokens)->token[i + 1] == '$' || (*tokens)->token[i + 1] == '\'' ||
		(*tokens)->token[i + 1] == '"' || (*tokens)->token[i + 1] == '\\'))
			i++;*/
		if (i != sindex && i != eindex)
		{
			new[j] = (*tokens)->token[i];
			j++;
		}
		i++;
	}
	new[j] = '\0';
	ft_printf("new %s\n", new);
	(*tokens)->flags &= ~DQ;
	free((*tokens)->token);
	(*tokens)->token = new;
	remove_esc(tokens);
}

void	remove_quotes(t_token **tokens)
{
	int i;

	i = 0;
	//len = get_quote_index((*tokens)->token, (*tokens)->flags);
	while((*tokens)->token[i] != '\0')
	{
		if ((*tokens)->token[i] == '\\')
			i++;
		else if ((*tokens)->flags & SQ && (*tokens)->token[i] == '\'')
			remove_squotes(tokens, i);
		else if((*tokens)->flags & DQ && (*tokens)->token[i] == '"')
			remove_dquotes(tokens, i);
		i++;
	}
}



void	remove_quoting(t_token **head)
{
	t_token *tmp;
	int		i;

	tmp = *head;
	i = 0;
	while(tmp != NULL)
	{
		if (tmp->type == WORD)
		{
			i = 0;
			remove_esc(&tmp);
			while(tmp->token[i] != '\0')
			{
				if (tmp->token[i] == '\\')
					i++;
				else if ((tmp->flags & SQ && tmp->token[i] == '\'') || (tmp->flags & DQ && tmp->token[i] == '"'))
				{
					remove_quotes(&tmp);
					//if(tmp->flags & DQ)
					//	remove_esc(&tmp->token);
				}
				i++;
			}

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
		else if (command[i] == '\'')
			i = i + count_squoting_word(&command[i], &flags);
		else if (command[i] == '"')
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
