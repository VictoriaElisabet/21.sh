/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 11:28:19 by vgrankul          #+#    #+#             */
/*   Updated: 2019/10/31 13:49:20 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//ta bort print token saan
void		print_token(t_token *head)
{
		t_token *tmp = head;
    while (tmp != NULL)
    {
        ft_printf("%s\n", tmp->token);
        tmp = tmp->next;
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

t_token		*create_token(int tok_type, char *tok)
{
	t_token *new;

	new = (t_token*)malloc(sizeof(t_token));
	new->token = ft_strdup(tok);
	free(tok);
	new->type = tok_type;
	new->flags = 0;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void		add_token(t_token **head, int tok_type, char *tok)
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