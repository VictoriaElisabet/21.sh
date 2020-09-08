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

int			count_argc(char **list, int start)
{
	int i;
	int count;

	i = start;
	count = 0;
	while(list[i] != NULL)
	{
		if (str_chr(list[i], '<') == 1 || str_chr(list[i], '>') == 1)
			i = i + 2;
		else
			count++;
		i++;
	}
	return(count);
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
			if (str_chr(words[i], '>') == 1 || str_chr(words[i], '<') == 1)
				i++;
			else if (!(command->argv[j++] = ft_strdup(words[i])))
				command->argv[j++] = NULL;
			i++;
			argc--;
		}
	}
	command->argv[j] = NULL;
}

t_command	*fill_command_struct(char *comm, t_command *command, char **words)
{
	int			argc;
	int			vars;
	//int			word_nbr;

	//set_struct(command); allt behöver sättas till noll innan något görs
	//set_redirections(words, command);
	//word_nbr = count_list(words);
	vars = count_vars(words);
	argc = count_argc(words, vars) - 1;
	if (!(command->command = ft_strdup(comm)))
		command->command = NULL;
	add_variables(words, command, vars);
	add_argv(words, command, vars, argc);
	command->argc = argc;
	//if (!(command->ctrl_op = ft_strdup(words[word_nbr - 1])))
	//	command->ctrl_op = NULL;
	return (command);
}

//ta bort funct
void		print_token(t_token *head)
{
		t_token *tmp = head;
    while (tmp != NULL)
    {
        ft_printf("%s\n", tmp->token);
        tmp = tmp->next;
    }
}

t_command	**create_command_struct_list(char **command_list, char **env)
{
	t_token		*tokens;
	t_command	**commands;
	int			i;

	i = 0;
	if ((commands = (t_command**)malloc(count_arr(command_list) * sizeof(t_command*) + 1)))
	{
		while (command_list[i] != NULL)
		{
			if ((tokens = create_tokens(command_list[i])))
			{
				word_expansion(&tokens, env);
				print_token(tokens);
				//if ((commands[i] = (t_command*)malloc(sizeof(t_command))))
				//	commands[i] = fill_command_struct(command_list[i], commands[i], words);
				destroy_tok_list(tokens);
			}
			i++;
		}
	}
	commands[i] = NULL;
	ft_printf("hii");
	return (commands);
}
