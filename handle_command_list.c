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

void	destroy_command(t_command *command)
{
	destroy_arr(command->variables);
	destroy_arr(command->argv);
	free(command->command);
	free(command->ctrl_op);
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
	t_command	*command;

	status = 0;
	i = 0;
	while (command_list[i] != NULL)
	{
		if ((command = create_command_struct(command_list[i], *env)))
			status = exec_command(command, command_list, env);
		if (ctrl_function(command->ctrl_op, status) != 1)
		{
			if (command_list[i + 1] != NULL)
				i++;
		}
		destroy_command(command);
		i++;
	}
	return (status);
}
