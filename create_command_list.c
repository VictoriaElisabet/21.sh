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

void		get_index(char *token, int *ctrl_op)
{
	int		i;
	char	types[7][3] = {"|", "||", "|&", "&", "&&", ";", "\n"};

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

void		set_argv(t_command *command, t_token *tokens, int argc)
{
	t_token *tmp;
	int		i;

	tmp = tokens;
	i = 0;
	if ((command->argv = (char**)malloc(argc * sizeof(char*) + 1)))
	{
		while (tmp != NULL)
		{
			if (tmp->type == REDIR)
				tmp = tmp->next;
			else if (tmp->type == WORD)
			{
				command->argv[i] = ft_strdup(tmp->token);
				i++;
			}
			tmp = tmp->next;
		}
	}
	command->argv[i] = NULL;
}

void		set_struct(t_command *command)
{
	command->tokens = NULL;
	command->argv = NULL;
	command->argc = 0;
	command->ctrl_op = 0;
}

void		copy_tokens(t_command *command, t_token **tok_ls)
{
	while ((*tok_ls)->type != OPERATOR)
	{
		add_token(&command->tokens, (*tok_ls)->type, (*tok_ls)->token,
		(*tok_ls)->flags);
		(*tok_ls) = (*tok_ls)->next;
	}
	add_token(&command->tokens, (*tok_ls)->type, (*tok_ls)->token,
	(*tok_ls)->flags);
	if ((*tok_ls)->type == OPERATOR)
		get_index((*tok_ls)->token, &command->ctrl_op);
}

t_command	*fill_command_struct(t_command *command,
t_token **tok_ls, char **env)
{
	set_struct(command);
	copy_tokens(command, tok_ls);
	token_expansion(&command->tokens, env);
	command->argc = count_words(command->tokens);
	set_argv(command, command->tokens, command->argc);
	return (command);
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

t_command	**create_command_list(char *prt_str, char **env)
{
	t_token		*tokens;
	t_token		*tmp;
	t_command	**commands;
	int			comm_nbr;
	int			i;

	tokens = create_tokens(prt_str);
	tmp = tokens;
	comm_nbr = count_ctrl_op(tokens);
	i = 0;
	if ((commands = (t_command**)malloc(comm_nbr * sizeof(t_command*) + 1)))
	{
		while (tmp != NULL)
		{
			if ((commands[i] = (t_command*)malloc(sizeof(t_command))))
				commands[i] = fill_command_struct(commands[i], &tmp, env);
			tmp = tmp->next;
			i++;
		}
		commands[i] = NULL;
	}
	destroy_tok_list(tokens);
	return (commands);
	//free tokens;
}
