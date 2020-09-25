/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <vgrankul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 11:28:19 by vgrankul          #+#    #+#             */
/*   Updated: 2020/09/16 15:17:15 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/21sh.h"

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

int		run_command(t_command *command, pid_t pid, char **env)
{
	char	*file_path;
	int		status;

	status = 0;
	if ((status = set_file_path(command, &file_path, env)) != 0)
		return (print_exec_error(command, status, file_path));
	if (command->fork == 0)
		pid = fork();
	if (pid == -1)
		return (print_exec_error(command, -1, file_path));
	if (pid == 0)
	{
		if ((execve(file_path, command->argv, env)) == -1)
			return (print_exec_error(command, status, file_path));
		free(file_path);
	}
	if ((command->ctrl_op & PIPE_OP) == 0)
		pid = waitpid(pid, &status, 0);
	return ((print_exec_error(command, status, file_path)));
}

int		exec_command(t_command *command, t_command **commands,
pid_t pid, char ***env)
{
	int status;

	status = 0;
	if (set_redirections(command) == -1)
	{
		reset_redirections(command->fd);
		return (-1);
	}
	if (command->argc != 0)
	{
		if (is_builtin(command) == 1)
			status = run_builtin(command, commands, env, status);
		else
		{
			status = run_command(command, pid, *env);
		}
	}
	reset_redirections(command->fd);
	return (status);
}
