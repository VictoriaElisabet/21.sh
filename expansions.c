/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 11:28:19 by vgrankul          #+#    #+#             */
/*   Updated: 2019/10/31 13:49:20 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_token(t_token **head, t_token *rem)
{
	ft_printf("token %s\n", rem->token);
	if (*head == NULL || rem == NULL)
		return ;
	if (*head == rem)
		*head = rem->next;
	if (rem->prev != NULL)
		rem->prev->next = rem->next;
	if (rem->next != NULL)
	{
		ft_printf("remne");
		rem->next->prev = rem->prev;
	}
	free(rem->token);
	free(rem);
	print_token(*head);
	//måst char token freas å annars var e leak?
}

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

void	word_expansion(t_token **head, char **env)
{
	t_token *tmp;

	remove_token(head, (*head)->next);
	tmp = *head;
	while (tmp->next != NULL)
	{
		if (str_chr(tmp->token, '\'') != 1)
		{
			if (str_chr(tmp->token, '"') != 1)
				tmp->token = tilde_expansion(tmp->token, env);
			if (ft_strcmp((tmp->token =
			parameter_expansion(tmp->token, env)), "\0") == 0)
			{
				ft_printf("hi");/*if ((tmp = remove_word((*words), i)))
				{
					destroy_arr((*words));
					(*words) = tmp;
				}*/
				remove_token(head, tmp);
				tmp = tmp->prev;
			}
		}
		tmp = tmp->next;
	}
}
