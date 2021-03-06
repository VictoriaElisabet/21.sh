/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <vgrankul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 11:28:19 by vgrankul          #+#    #+#             */
/*   Updated: 2020/09/16 15:17:07 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	remove_token(t_token **head, t_token *rem)
{
	t_token *tmp;

	if ((*head) == NULL || rem == NULL)
		return ;
	if ((*head) == rem)
		(*head) = rem->next;
	else
	{
		tmp = *head;
		while (tmp->next != rem)
			tmp = tmp->next;
		if (tmp->next == NULL)
			return ;
		else if (tmp->next->next == NULL)
			tmp->next = NULL;
		else
		{
			rem = tmp->next;
			tmp->next = rem->next;
			rem->next->prev = tmp;
		}
	}
	free(rem->token);
	free(rem);
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

void	token_expansion(t_token **head, char **env)
{
	t_token *tmp;

	tmp = *head;
	while (tmp != NULL)
	{
		if ((ft_strcmp(tmp->token, "<<") == 0
		|| ft_strcmp(tmp->token, "<<-") == 0) &&
		(tmp->next->flags & DQ || tmp->next->flags & SQ))
		{
			ft_printf("hii");
			tmp = tmp->next;
		}
		else if (tmp->type == WORD)
		{
			if (tmp->token[0] == '~')
				tmp->token = tilde_expansion(tmp->token, env);
			if (ft_strcmp((tmp->token =
			parameter_expansion(tmp, tmp->token, env)), "\0") == 0)
				remove_token(head, tmp);
		}
		tmp = tmp->next;
	}
}
