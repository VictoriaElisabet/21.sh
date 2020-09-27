/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <vgrankul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 11:28:19 by vgrankul          #+#    #+#             */
/*   Updated: 2020/09/16 15:35:30 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void		set_op_list(char types[7][3])
{
	ft_strcpy(types[0], "|");
	ft_strcpy(types[1], "||");
	ft_strcpy(types[2], "|&");
	ft_strcpy(types[3], "&");
	ft_strcpy(types[4], "&&");
	ft_strcpy(types[5], ";");
	ft_strcpy(types[6], "\n");
}

void		get_index(char *token, int *ctrl_op)
{
	int		i;
	char	types[7][3];

	set_op_list(types);
	i = 0;
	while (i < 7)
	{
		if (ft_strcmp(types[i], token) == 0)
			*ctrl_op |= 1 << i;
		i++;
	}
}

int			count_words(t_token *tokens)
{
	int		count;
	t_token *tmp;

	count = 0;
	tmp = tokens;
	while (tmp != NULL)
	{
		if (tmp->type == REDIR)
			tmp = tmp->next;
		else if (tmp->type == WORD)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

int			count_ctrl_op(t_token *tokens)
{
	t_token *tmp;
	int		count;

	count = 0;
	tmp = tokens;
	while (tmp != NULL)
	{
		if (tmp->type == OPERATOR)
			count++;
		tmp = tmp->next;
	}
	return (count);
}
