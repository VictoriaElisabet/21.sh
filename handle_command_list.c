/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_command_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <vgrankul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 11:28:19 by vgrankul          #+#    #+#             */
/*   Updated: 2020/09/16 15:16:51 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	destroy_command(t_command **command)
{
	int i;

	i = 0;
	while (command[i] != NULL)
	{
		destroy_arr(command[i]->argv);
		destroy_tok_list(command[i]->tokens);
		free(command[i]);
		i++;
	}
	free(command);
}

int		ctrl_function(int ctrl_op, int status)
{
	if ((ctrl_op & OR_OP) && status != 0)
		return (1);
	if ((ctrl_op & AND_OP) && status == 0)
		return (1);
	if ((ctrl_op & SEMI) || (ctrl_op & NEWLINE) || (ctrl_op & PIPE_OP))
		return (1);
	return (0);
}

int		handle_command_list(t_command **commands, char ***env)
{
	int			status;
	int			i;
	pid_t		pid;

	status = 0;
	i = 0;
	while (commands[i] != NULL)
	{
		if (commands[i]->ctrl_op & PIPE_OP)
		{
			status = create_pipe(&commands[i], env, &i);
			//i = i + 2;
		}
		else if (is_builtin(commands[i]) == 1)
			status = run_builtin(commands[i], commands, env, status);
		else
		{
			pid = fork(); // om he failar
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
