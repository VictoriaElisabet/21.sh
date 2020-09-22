/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <vgrankul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 11:28:19 by vgrankul          #+#    #+#             */
/*   Updated: 2020/09/16 15:17:34 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int		get_quote_index(char *token, int flags)
{
	int len;
	int c;

	len = ft_strlen(token);
	c = (flags & SQ) ? '\'' : '"';
	while (len > 0)
	{
		if (token[len] == c)
			return (len);
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
		i++;
	}
	new[j] = '\0';
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
		if (i != sindex && i != eindex)
		{
			new[j] = (*tokens)->token[i];
			j++;
		}
		i++;
	}
	new[j] = '\0';
	free((*tokens)->token);
	(*tokens)->token = new;
}

void	remove_quotes(t_token **tokens)
{
	int i;

	i = 0;
	while ((*tokens)->token[i] != '\0')
	{
		if ((*tokens)->token[i] == '\\')
			i++;
		else if ((*tokens)->flags & SQ && (*tokens)->token[i] == '\'')
			remove_squotes(tokens, i);
		else if ((*tokens)->flags & DQ && (*tokens)->token[i] == '"')
			remove_dquotes(tokens, i);
		i++;
	}
	(*tokens)->flags &= ~SQ;
	if ((*tokens)->flags & DQ)
	{
		(*tokens)->flags &= ~DQ;
		remove_esc(tokens);
	}
}

void	remove_quoting(t_token **head)
{
	t_token *tmp;
	int		i;

	tmp = *head;
	i = 0;
	while (tmp != NULL)
	{
		if (tmp->type == WORD)
		{
			i = 0;
			remove_esc(&tmp);
			while (tmp->token[i] != '\0')
			{
				if (tmp->token[i] == '\\')
					i++;
				else if ((tmp->flags & SQ && tmp->token[i] == '\'') ||
				(tmp->flags & DQ && tmp->token[i] == '"'))
					remove_quotes(&tmp);
				i++;
			}
		}
		tmp = tmp->next;
	}
}
