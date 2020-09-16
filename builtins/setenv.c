/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <vgrankul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 11:28:19 by vgrankul          #+#    #+#             */
/*   Updated: 2020/09/16 15:19:32 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**add_env(const char *name, const char *value, char **env, int count)
{
	int		i;
	char	**new;
	char	*tmp;

	i = 0;
	if ((new = (char**)malloc(count * sizeof(char*) + 1)))
	{
		while (env[i] != NULL)
		{
			if (!(new[i] = ft_strdup(env[i])))
				return (NULL);
			i++;
		}
		if ((tmp = ft_strjoin(name, "=")))
		{
			if (!(new[i] = ft_strjoin(tmp, value)))
				return (NULL);
			free(tmp);
			i++;
		}
	}
	new[i] = NULL;
	return (new);
}

char	*get_env_name(char *env)
{
	int		i;
	char	*name;

	i = 0;
	while (env[i] != '\0' && env[i] != '=')
		i++;
	if ((name = ft_strsub(env, 0, i)))
		return (name);
	return (NULL);
}

int		set_env(const char *name, const char *value, char **env)
{
	int		i;
	char	*tmp;
	char	*env_name;

	i = 0;
	if (!(name))
		return (EXIT_FAILURE);
	while (env[i] != NULL)
	{
		if (ft_strcmp(name, (env_name = get_env_name(env[i]))) == 0)
		{
			free(env[i]);
			if ((tmp = ft_strjoin(name, "=")))
			{
				if (!(env[i] = ft_strjoin(tmp, value)))
					return (EXIT_FAILURE);
				free(tmp);
			}
			free(env_name);
			return (0);
		}
		free(env_name);
		i++;
	}
	return (i);
}

int		ft_setenv(int argc, char *name, char *value, char ***env)
{
	int		index;
	char	**tmp;
	char	*val;

	if (argc < 2 || argc > 3)
	{
		ft_printf("Incorrect number of arguments\n");
		return (-1);
	}
	if (name == NULL || ft_strlen(name) == 0 || str_chr(name, '=') == 1)
		return (EXIT_FAILURE);
	if (value != NULL)
		val = value;
	else
		val = "\0";
	if ((index = set_env(name, val, *env)) != 0)
	{
		if (index == -1)
			return (EXIT_FAILURE);
		if (!(tmp = add_env(name, val, *env, index + 1)))
			return (EXIT_FAILURE);
		destroy_arr(*env);
		*env = tmp;
	}
	return (0);
}
