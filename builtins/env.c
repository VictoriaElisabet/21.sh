/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <vgrankul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 11:28:19 by vgrankul          #+#    #+#             */
/*   Updated: 2020/09/16 15:19:16 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	remove_env_arg(char ***argv, int i)
{
	char	**new;
	int		j;

	j = 0;
	new = (char**)malloc(count_arr(&(*argv)[i]) * sizeof(char*) + 1);
	while((*argv)[i] != NULL)
	{
		if (ft_strcmp((*argv)[i], "env") != 0)
		{
			new[j] = ft_strdup((*argv)[i]);
			j++;
		}
		i++;
	}
	new[j] = NULL;
	destroy_arr(*argv);
	*argv = new;
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

int		run_env_cmd(t_command *command, t_command **commands, char ***tmp, int i)
{
	int		status;
	pid_t	pid;

	status = 0;
	pid = fork();
	remove_env_arg(&command->argv, i);
	exec_command(command, commands, pid ,tmp);
	waitpid(pid, &status, 0);
	return (status);
}

int		ft_env(t_command *command, t_command **commands, char **env)
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
			status = run_env_cmd(command, commands, &tmp, i);
		else
			print_env(tmp);
	}
	destroy_arr(tmp);
	return (status);
}
