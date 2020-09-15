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
	if ((ctrl_op & SEMI) || (ctrl_op & NEWLINE))
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
	//set up redirections
	/*while(commands[i] != NULL)
	{
		set_redirections(commands[i]);
		ft_printf("ny command\n");
		ft_printf("argc %d= arguments\n", commands[i]->argc);
		int j = 0;
		while(commands[i]->argv[j] != NULL)
		{
			ft_printf("%s\n", commands[i]->argv[j]);
			j++;
		}
		ft_printf("tokens\n");
		print_token(commands[i]->tokens);
		i++;
	}*/
	while (commands[i] != NULL)
	{
		//if ((command = create_command_struct(command_list[i], *env)))
		/*if (commands[i]->ctrl_op & PIPE_OP)
		{
			status = create_pipe(&commands[i], env);
			//i++;
		} */
		if (is_builtin(commands[i]) == 1)
		{
			status = run_builtin(commands[i], commands, env, status);
		}
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
		//reset_redirections(commands[i]->fd);
		i++;
	}
	destroy_command(commands);
	return (status); // return print _exec erro
}
