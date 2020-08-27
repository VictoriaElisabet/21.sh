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

int			count_vars(char **list)
{
	int i;

	i = 0;
	while (list[i] != NULL && str_chr(list[i], '=') == 1)
		i++;
	return (i);
}

void		add_variables(char **words, t_command *command, int vars)
{
	int i;

	i = 0;
	if ((command->variables = (char**)malloc(vars * sizeof(char*) + 1)))
	{
		while (words[i] != NULL && vars > 0)
		{
			if (!(command->variables[i] = ft_strdup(words[i])))
				command->variables[i] = NULL;
			i++;
			vars--;
		}
	}
	command->variables[i] = NULL;
}

void		add_argv(char **words, t_command *command, int start, int argc)
{
	int i;
	int j;

	i = start;
	j = 0;
	if ((command->argv = (char**)malloc(argc * sizeof(char*) + 1)))
	{
		while (words[i] != NULL && argc > 0)
		{
			if (!(command->argv[j] = ft_strdup(words[i])))
				command->argv[j] = NULL;
			i++;
			j++;
			argc--;
		}
	}
	command->argv[j] = NULL;
}

t_command	*fill_command_struct(char *comm, t_command *command, char **words)
{
	int			argc;
	int			vars;
	int			word_nbr;

	word_nbr = count_list(words);
	vars = count_vars(words);
	argc = word_nbr - vars - 1;
	if (!(command->command = ft_strdup(comm)))
		command->command = NULL;
	add_variables(words, command, vars);
	add_argv(words, command, vars, argc);
	command->argc = argc;
	if (!(command->ctrl_op = ft_strdup(words[word_nbr - 1])))
		command->ctrl_op = NULL;
	return (command);
}

t_command	*create_command_struct(char *cmd, char **env)
{
	char		**words;
	t_command	*command;
	int			count;

	count = 0;
	if ((words = word_splitting(cmd, count)))
	{
		word_expansion(&words, env);
		if ((command = (t_command*)malloc(sizeof(t_command))))
			command = fill_command_struct(cmd, command, words);
		destroy_arr(words);
	}
	return (command);
}
