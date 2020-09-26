/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <vgrankul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 11:28:19 by vgrankul          #+#    #+#             */
/*   Updated: 2020/09/16 15:19:38 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

char	**remove_env(const char *name, char **env)
{
	int		i;
	int		j;
	char	**new;
	int		count;
	char	*env_name;

	i = 0;
	j = 0;
	count = count_arr(env) - 1;
	if ((new = (char**)malloc((count * sizeof(char*) + 1))))
	{
		while (j < count)
		{
			if (ft_strcmp(name, (env_name = get_env_name(env[i]))) == 0)
				i++;
			if (!(new[j] = ft_strdup(env[i])))
				return (NULL);
			i++;
			j++;
			free(env_name);
		}
	}
	new[j] = NULL;
	return (new);
}

int		ft_unsetenv(int argc, char **argv, char ***env)
{
	char **tmp;

	if (argc != 2)
	{
		ft_printf("Incorrect number of arguments\n");
		return (2);
	}
	if (argv[1] == NULL || ft_strlen(argv[1]) == 0 ||
		str_chr(argv[1], '=') == 1)
		return (EXIT_FAILURE);
	if (find_env(argv[1], *env) == 0)
	{
		if (!(tmp = remove_env(argv[1], *env)))
			return (EXIT_FAILURE);
		destroy_arr(*env);
		*env = tmp;
	}
	return (0);
}
