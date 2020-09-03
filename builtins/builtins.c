/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 11:28:19 by vgrankul          #+#    #+#             */
/*   Updated: 2019/10/31 13:49:20 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		run_builtin(t_command *command, t_command **commands, char ***env,
int status)
{
	if (ft_strcmp(command->argv[0], "cd") == 0)
		return (ft_cd(command->argc, command->argv, env));
	if (ft_strcmp(command->argv[0], "echo") == 0)
		return (ft_echo(command->argv));
	if (ft_strcmp(command->argv[0], "exit") == 0)
		return (ft_exit(command, commands, env, status));
	if (ft_strcmp(command->argv[0], "env") == 0)
		return (ft_env(command, *env));
	if (ft_strcmp(command->argv[0], "setenv") == 0)
	{
		return (ft_setenv(command->argc, command->argv[1],
		command->argv[2], env));
	}
	if (ft_strcmp(command->argv[0], "unsetenv") == 0)
		return (ft_unsetenv(command->argc, command->argv, env));
	return (1);
}

int		is_builtin(t_command *command)
{
	if (ft_strcmp(command->argv[0], "cd") == 0)
		return (1);
	if (ft_strcmp(command->argv[0], "echo") == 0)
		return (1);
	if (ft_strcmp(command->argv[0], "exit") == 0)
		return (1);
	if (ft_strcmp(command->argv[0], "env") == 0)
		return (1);
	if (ft_strcmp(command->argv[0], "setenv") == 0)
		return (1);
	if (ft_strcmp(command->argv[0], "unsetenv") == 0)
		return (1);
	return (0);
}
