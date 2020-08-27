/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 11:28:19 by vgrankul          #+#    #+#             */
/*   Updated: 2019/10/31 13:49:20 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*new_command(char **argv, char *ctrl_op, int i)
{
	char	*arg;
	char	*tmp;
	char	*command;

	command = ft_strnew(1);
	while (argv[i] != NULL)
	{
		arg = ft_strjoin(argv[i], " ");
		tmp = ft_strjoin(command, arg);
		free(arg);
		free(command);
		command = tmp;
		i++;
	}
	arg = ft_strjoin(ctrl_op, " ");
	tmp = ft_strjoin(command, arg);
	free(arg);
	free(command);
	command = tmp;
	return (command);
}

int		update_env(char *argv, char ***tmp)
{
	char	*name;
	char	*value;
	int		status;

	status = 0;
	name = set_name(argv);
	value = set_value(argv);
	status = ft_setenv(2, name, value, tmp);
	free(name);
	free(value);
	return (status);
}

int		run_env_cmd(t_command *command, char ***tmp, int i)
{
	char	*comm;
	char	**command_list;
	int		status;

	status = 0;
	if ((comm = new_command(command->argv, command->ctrl_op, i)))
	{
		if ((command_list = create_command_list(comm)))
			status = handle_command_list(command_list, tmp);
	}
	free(comm);
	destroy_arr(command_list);
	return (status);
}

int		ft_env(t_command *command, char **env)
{
	char	**tmp;
	int		i;
	int		status;

	status = 0;
	tmp = copy_env(env);
	if (command->argc == 1)
		print_env(env);
	else
	{
		i = 1;
		while (command->argv[i] != NULL &&
		(str_chr(command->argv[i], '=') == 1))
		{
			status = update_env(command->argv[i], &tmp);
			i++;
		}
		if (command->argv[i] != NULL)
			status = run_env_cmd(command, &tmp, i);
		else
			print_env(tmp);
	}
	destroy_arr(tmp);
	return (status);
}
