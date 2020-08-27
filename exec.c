/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 11:28:19 by vgrankul          #+#    #+#             */
/*   Updated: 2019/10/31 13:49:20 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*search_path(char *name, char *path)
{
	DIR				*dir;
	struct dirent	*dirent;
	char			*file_path;
	char			*tmp;

	if ((dir = opendir(path)))
	{
		while ((dirent = readdir(dir)) != NULL)
		{
			if (ft_strcmp(dirent->d_name, name) == 0)
			{
				if ((tmp = ft_strjoin(path, "/")))
				{
					if ((file_path = ft_strjoin(tmp, name)))
					{
						free(tmp);
						closedir(dir);
						return (file_path);
					}
				}
			}
		}
		closedir(dir);
	}
	return (NULL);
}

char	*find_executable(char *name, char **env)
{
	char	*path;
	char	**paths;
	char	*file_path;
	int		i;

	i = 0;
	if ((path = get_env_value("PATH", env)))
	{
		if ((paths = ft_strsplit(path, ':')))
		{
			while (paths[i] != NULL)
			{
				if ((file_path = search_path(name, paths[i])) != NULL)
				{
					destroy_arr(paths);
					return (file_path);
				}
				i++;
			}
		}
		destroy_arr(paths);
	}
	return (NULL);
}

char	set_file_path(t_command *command, char **file_path, char **env)
{
	if (str_chr(command->argv[0], '/') == 1)
	{
		*file_path = ft_strdup(command->argv[0]);
		if (access(*file_path, F_OK) == -1)
			return (125);
	}
	else
	{
		if (!(*file_path = find_executable(command->argv[0], env)))
			return (127);
	}
	if (access(*file_path, X_OK) == -1)
		return (126);
	return (0);
}

int		run_command(t_command *command, char **env)
{
	pid_t	pid;
	char	*file_path;
	int		status;

	status = 0;
	if ((status = set_file_path(command, &file_path, env)) != 0)
		return (print_exec_error(command, status, file_path));
	pid = fork();
	if (pid == -1)
		return (print_exec_error(command, EXIT_FAILURE, file_path));
	if (pid == 0)
	{
		if ((execve(file_path, command->argv, env)) == -1)
			return (print_exec_error(command, status, file_path));
		free(file_path);
	}
	else
		pid = waitpid(pid, &status, 0);
	return ((print_exec_error(command, status, file_path)));
}

int		exec_command(t_command *command, char **command_list, char ***env)
{
	int status;

	status = 0;
	if (command->argc != 0)
	{
		if (is_builtin(command) == 1)
			status = run_builtin(command, command_list, env, status);
		else
			status = run_command(command, *env);
	}
	return (status);
}
