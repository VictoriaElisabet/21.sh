/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 11:28:19 by vgrankul          #+#    #+#             */
/*   Updated: 2019/10/31 13:49:20 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		count_ctrl_op(char *prt_str, int count)
{
	int i;

	i = 0;
	while (prt_str[i] != '\0')
	{
		if (prt_str[i] == '"' || prt_str[i] == '\'')
		{
			i++;
			while (prt_str[i] != '"' && prt_str[i] != '\'' &&
			prt_str[i] != '\0')
				i++;
		}
		if (prt_str[i + 1] == '\0' && prt_str[i] != ';' && prt_str[i] != '|' &&
		prt_str[i] != '&')
			count++;
		if (prt_str[i] == '|' || prt_str[i] == '&' || prt_str[i] == ';')
		{
			if (prt_str[i + 1] == '|' || prt_str[i + 1] == '&')
				i++;
			count++;
		}
		i++;
	}
	return (count);
}

int		count_commlength(char *prt_str)
{
	int i;

	i = 0;
	while (prt_str[i] != '\0')
	{
		if (prt_str[i] == '"' || prt_str[i] == '\'')
		{
			i++;
			while (prt_str[i] != '"' && prt_str[i] != '\'' &&
			prt_str[i] != '\0')
				i++;
		}
		if (prt_str[i] == '|' || prt_str[i] == '&' || prt_str[i] == ';')
		{
			i++;
			if (prt_str[i] == '|' || prt_str[i] == '&')
				i++;
			break ;
		}
		i++;
	}
	return (i);
}

char	**create_command_list(char *prt_str)
{
	char	**commands;
	int		i;
	int		j;
	int		comms;
	int		count;

	j = 0;
	i = 0;
	count = 0;
	comms = count_ctrl_op(prt_str, count);
	if ((commands = (char**)malloc(comms * sizeof(char*) + 1)))
	{
		while (j < comms)
		{
			if ((commands[j] =
			ft_strsub(&prt_str[i], 0, count_commlength(&prt_str[i]))))
				i = i + count_commlength(&prt_str[i]);
			j++;
		}
	}
	commands[j] = NULL;
	free(prt_str);
	return (commands);
}
