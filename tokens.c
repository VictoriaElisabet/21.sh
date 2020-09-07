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

int		is_part_op(int c)
{
	if (c == '|' || c == '&' || c == ';' || c == '\n' || c == '<' || c == '>')
		return (1);
	return (0);
}

t_token		*create_tokens(char *command)
{
	t_token		*head;
	int			i;

	while (command[i] != '\0')
	{

	}
}