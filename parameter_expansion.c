/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_expansion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <vgrankul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 11:28:19 by vgrankul          #+#    #+#             */
/*   Updated: 2020/09/16 15:15:58 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

char	*get_name(char *param)
{
	int		i;
	int		len;
	char	*name;

	i = 0;
	len = ft_strlen(param);
	if (param == NULL)
		return ("\0");
	while (ft_isalnum(param[i]) != 1 && param[i] != '\0' && len-- > 0)
	{
		if (param[i] == '{')
			len--;
		i++;
	}
	name = ft_strsub(&param[i], 0, len);
	return (name);
}

int		get_param(char *word, char **param)
{
	int		i;

	i = 1;
	if (word[i] == '{')
	{
		while (word[i] != '}')
			i++;
		i++;
	}
	else
	{
		while (word[i] != '$' && word[i] != '"' && word[i] != '\0' &&
		word[i] != '}')
			i++;
	}
	*param = ft_strsub(word, 0, i);
	return (i);
}

char	*expand_param(char *param, char **env)
{
	char	*value;
	int		i;
	char	*name;

	i = 0;
	if ((name = get_name(param)))
	{
		while (env[i] != NULL)
		{
			if (find_env(name, env) == 0)
			{
				value = get_env_value(name, env);
				free(name);
				return (value);
			}
			i++;
		}
		free(name);
	}
	return ("\0");
}

void	set_word(char **word, char *temp, char *value, int i)
{
	char	*tmp;

	tmp = ft_strjoin(temp, value);
	free(temp);
	value = ft_strsub((*word), i, strlen(&(*word)[i]));
	temp = ft_strjoin(tmp, value);
	free((*word));
	free(value);
	free(tmp);
	(*word) = temp;
}

char	*parameter_expansion(char *word, char **env)
{
	int		i;
	char	*value;
	char	*param;
	char	*temp;

	i = 0;
	while (word[i] != '\0')
	{
		if (word[i] == '$')
		{
			if ((temp = ft_strsub(word, 0, i)))
			{
				i = i + get_param(&word[i], &param);
				if ((param))
				{
					value = expand_param(param, env);
					set_word(&word, temp, value, i);
					free(param);
				}
			}
		}
		i++;
	}
	return (word);
}
