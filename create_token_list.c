/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <vgrankul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 11:28:19 by vgrankul          #+#    #+#             */
/*   Updated: 2020/09/16 15:17:42 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/shell.h"

void		destroy_tok_list(t_token *head)
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

t_token		*create_token(int tok_type, char *tok, int flags)
{
	t_token *new;

	new = NULL;
	if ((new = (t_token*)malloc(sizeof(t_token))))
	{
		new->token = ft_strdup(tok);
		new->type = tok_type;
		new->flags = flags;
		new->next = NULL;
		new->prev = NULL;
	}
	return (new);
}

void		add_token(t_token **head, int tok_type, char *tok, int flags)
{
	t_token	*new;
	t_token *tmp;

	if ((new = create_token(tok_type, tok, flags)))
	{
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
			new->prev = tmp;
		}
	}
}
