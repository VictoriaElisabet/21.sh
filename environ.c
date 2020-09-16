/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <vgrankul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 11:28:19 by vgrankul          #+#    #+#             */
/*   Updated: 2020/09/16 15:17:23 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

char	*env_strchr(const char *s, int c)
{
	char value;
	char *str;

	value = (char)c;
	str = (char*)s;
	if (value == '\0')
		return (&str[ft_strlen(str)]);
	while (*str != '\0')
	{
		if (*str == value)
		{
			str++;
			return (str);
		}
		str++;
	}
	return (NULL);
}

int		count_arr(char **arr)
{
	int i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i);
}

char	*get_env_value(char *name, char **env)
{
	int		i;
	char	*value;

	i = 0;
	if (!(name))
		return (NULL);
	while (env[i] != NULL)
	{
		if (ft_strncmp(name, env[i], ft_strlen(name)) == 0)
		{
			if ((value = env_strchr(env[i], '=')))
				return (value);
		}
		i++;
	}
	return (NULL);
}

int		find_env(const char *name, char **env)
{
	int		i;
	char	*env_name;

	i = 0;
	if (!(name))
		return (EXIT_FAILURE);
	while (env[i] != NULL)
	{
		if (ft_strcmp(name, (env_name = get_env_name(env[i]))) == 0)
		{
			free(env_name);
			return (0);
		}
		free(env_name);
		i++;
	}
	return (i);
}

char	**copy_env(char **environ)
{
	int		i;
	char	**env;

	i = 0;
	if ((env = (char**)malloc(count_arr(environ) * sizeof(char*) + 1)))
	{
		while (environ[i] != NULL)
		{
			if (ft_strncmp(environ[i], "SHELL=", 6) == 0)
			{
				env[i] =
				ft_strdup("SHELL=/home/vgrankul/projects/minishell/minishell");
				if (!(env[i]))
					return (NULL);
			}
			else
			{
				if (!(env[i] = ft_strdup(environ[i])))
					return (NULL);
			}
			i++;
		}
	}
	env[i] = NULL;
	return (env);
}
