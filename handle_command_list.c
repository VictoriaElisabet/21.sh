/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_command_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 11:28:19 by vgrankul          #+#    #+#             */
/*   Updated: 2019/10/31 13:49:20 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	destroy_command(t_command **command)
{
	int i;

	i = 0;
	while (command[i] != NULL)
	{
		destroy_arr(command[i]->variables);
		destroy_arr(command[i]->argv);
		free(command[i]->command);
		free(command[i]->ctrl_op);
		if(command[i]->infile != NULL)
			free(command[i]->infile);
		if(command[i]->outfile != NULL)
			free(command[i]->outfile);
		free(command[i]);
		i++;
	}
	free(command);
}

int		ctrl_function(char *ctrl_op, int status)
{
	if ((ft_strcmp(ctrl_op, "||") == 0) && status != 0)
		return (1);
	if ((ft_strcmp(ctrl_op, "&&") == 0) && status == 0)
		return (1);
	if (ft_strcmp(ctrl_op, ";") == 0 || ft_strcmp(ctrl_op, "\n") == 0)
		return (1);
	return (0);
}

int		handle_command_list(char **command_list, char ***env)
{
	int			status;
	int			i;
	t_command	**commands;
	pid_t		pid;

	status = 0;
	i = 0;
	commands = create_command_struct(command_list, *env);
	destroy_arr(command_list);
	while (commands[i] != NULL)
	{
		//if ((command = create_command_struct(command_list[i], *env)))
		if (ft_strcmp(commands[i]->ctrl_op, "|") == 0)
		{
			status = create_pipe(commands[i], commands[i + 1], commands, env);
			//i++;
		} 
		else if (is_builtin(commands[i]) == 1)
		{
			status = run_builtin(commands[i], commands, env, status);
		}
		else
		{
			pid = fork();
			exec_command(commands[i], commands, pid, env);
			waitpid(pid, &status, 0);
		}
		
		if (ctrl_function(commands[i]->ctrl_op, status) != 1)
		{
			if (commands[i + 1] != NULL)
				i++;
		}
		i++;
	}

	destroy_command(commands);
	return (status); // return print _exec erro
}
