/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command_struct.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 11:28:19 by vgrankul          #+#    #+#             */
/*   Updated: 2019/10/31 13:49:20 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_struct(t_command *command)
{
	command->command = NULL;
	command->variables = NULL;
	command->argv = NULL;
	command->argc = 0;
	command->L = 0;
	command->LL = 0;
	command->G = 0;
	command->GG = 0;
	command->infile = NULL;
	command->outfile = NULL;
}

void    set_redirections(char **words, t_command *command)
{
	int i;

	i = 0;
	while (words[i] != NULL)
	{
		if ((command->L = (ft_strcmp(words[i], "<") == 0) ? 1 : 0) == 1 || (command->LL = (ft_strcmp(words[i], "<<") == 0) ? 1 : 0) == 1)
			command->infile = ft_strdup(words[i + 1]);
		if ((command->G = (ft_strcmp(words[i], ">") == 0) ? 1 : 0) == 1 || (command->GG = (ft_strcmp(words[i], ">>") == 0) ? 1 : 0) == 1)
			command->outfile = ft_strdup(words[i + 1]);
		i++;
	}
	//ft_printf("infile och outfile%s %s\n", command->infile, command->outfile);
}