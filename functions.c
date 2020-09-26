/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <vgrankul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 11:28:19 by vgrankul          #+#    #+#             */
/*   Updated: 2020/09/16 15:16:59 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/shell.h"

int		count_list(char **list)
{
	int i;

	i = 0;
	while (list[i] != NULL)
		i++;
	return (i);
}

int		print_exec_error(t_command *command, int status, char *file_path)
{
	if (file_path != NULL)
		free(file_path);
	if (status == 125)
	{
		ft_printf("%s: No such file or directory\n", command->argv[0]);
		return (125);
	}
	else if (status == 126)
	{
		ft_printf("%s: command not an executable\n", command->argv[0]);
		return (126);
	}
	else if (status == 127)
	{
		ft_printf("%s: command not found\n", command->argv[0]);
		return (127);
	}
	else if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 11)
			ft_printf("Segmentation fault\n");
	}
	return (EXIT_SUCCESS);
}

void	print_env(char **env)
{
	int i;

	i = 0;
	while (env[i] != NULL)
	{
		ft_printf("%s\n", env[i]);
		i++;
	}
}

char	*set_value(char *argv)
{
	int		i;
	char	*value;

	i = 0;
	while (argv[i] != '\0' && argv[i] != '=')
		i++;
	value = ft_strsub(argv, i + 1, ft_strlen(argv) - (i + 1));
	return (value);
}

char	*set_name(char *argv)
{
	int		i;
	char	*name;

	i = 0;
	while (argv[i] != '\0' && argv[i] != '=')
		i++;
	name = ft_strsub(argv, 0, i);
	return (name);
}
