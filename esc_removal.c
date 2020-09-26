/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   esc_removal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <vgrankul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 11:28:19 by vgrankul          #+#    #+#             */
/*   Updated: 2020/09/16 15:17:34 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/shell.h"

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

	i = 0;
	while ((*tokens)->token[i] != '\0')
	{
		if ((*tokens)->flags & SQ && (*tokens)->token[i] == '\'')
			i = get_quote_index((*tokens)->token, (*tokens)->flags);
		else if ((*tokens)->flags & DQ && (*tokens)->token[i] == '"')
			i = get_quote_index((*tokens)->token, (*tokens)->flags);
		else if ((*tokens)->token[i] == '\\')
			remove_esc_sign(&(*tokens)->token, i);
		i++;
	}
}
