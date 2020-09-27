/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <vgrankul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 11:28:19 by vgrankul          #+#    #+#             */
/*   Updated: 2020/09/16 15:13:35 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

char	*get_value(char *t_prefix, char **env)
{
	char *value;

	if ((ft_strcmp(t_prefix, "~/") == 0 || ft_strcmp(t_prefix, "~") == 0) &&
		(value = get_env_value("HOME", env)) != NULL)
		return (value);
	else if (ft_strcmp(&t_prefix[1], (value = get_env_value("USER", env))) == 0)
	{
		if ((value = get_env_value("HOME", env)) != NULL)
			return (value);
	}
	else if (ft_strcmp(t_prefix, "~+") == 0 &&
		(value = get_env_value("PWD", env)) != NULL)
		return (value);
	else if (ft_strcmp(t_prefix, "~-") == 0 &&
		(value = get_env_value("OLDPWD", env)) != NULL)
		return (value);
	return (NULL);
}

char	*tilde_expansion(char *word, char **env)
{
	int		i;
	char	*t_prefix;
	char	*value;
	char	*tmp;

	i = 0;
	value = NULL;
	if (word[0] == '~')
	{
		while (word[i] != '/' && word[i] != '\0')
			i++;
		if ((t_prefix = ft_strsub(word, 0, i)) != NULL)
		{
			if ((value = get_value(t_prefix, env)) != NULL)
			{
				if ((tmp = ft_strjoin(value, &word[i])) != NULL)
				{
					free(word);
					word = tmp;
				}
			}
		}
		free(t_prefix);
	}
	return (word);
}
