/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 11:28:19 by vgrankul          #+#    #+#             */
/*   Updated: 2019/10/31 13:49:20 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_exit(t_command *command, t_command **commands, char ***env, int status)
{
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
		exit(ft_atoi(command->argv[1]));
	}
	return (0);
}
