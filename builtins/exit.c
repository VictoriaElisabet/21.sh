/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <vgrankul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 11:28:19 by vgrankul          #+#    #+#             */
/*   Updated: 2020/09/16 15:19:25 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/21sh.h"

int	ft_exit(t_command *command, t_command **commands, char ***env, int status)
{
	int exit_code;

	exit_code = command->argv[1] != NULL ? ft_atoi(command->argv[1]) : status;
	if (command->argc > 2)
		ft_printf("%s: too many arguments\n", command->argv[0]);
	else if (command->argc < 2)
	{
		destroy_command(commands);
		destroy_arr(*env);
		exit(status);
	}
	else
	{
		destroy_command(commands);
		destroy_arr(*env);
		exit(exit_code);
	}
	return (0);
}
