/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <vgrankul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 11:28:19 by vgrankul          #+#    #+#             */
/*   Updated: 2020/09/16 15:18:54 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/21sh.h"

int		change_wdir(char *path, char **argv, char ***env)
{
	char	*old_pwd;
	char	*pwd;

	if (!(old_pwd = getcwd(NULL, 0)))
		return (EXIT_FAILURE);
	if (chdir(path) == -1)
	{
		free(old_pwd);
		ft_printf("%s: %s: No such file or directory\n", argv[0], path);
		return (EXIT_FAILURE);
	}
	if (!(pwd = getcwd(NULL, 0)))
		return (EXIT_FAILURE);
	if ((ft_setenv(2, "PWD", pwd, env) != 0) ||
	(ft_setenv(2, "OLDPWD", old_pwd, env) != 0))
	{
		free(old_pwd);
		free(pwd);
		return (EXIT_FAILURE);
	}
	free(pwd);
	free(old_pwd);
	return (0);
}

int		print_error(char *s, char **argv)
{
	ft_printf("%s: ", argv[0]);
	ft_printf("%s\n", s);
	return (EXIT_FAILURE);
}

int		ft_cd(int argc, char **argv, char ***env)
{
	char	*path;

	if (argc > 2)
	{
		ft_printf("%s: too many arguments\n", argv[0]);
		return (2);
	}
	else if (argv[1] == NULL)
	{
		if (!(path = get_env_value("HOME", *env)))
			return (print_error("HOME not set", argv));
	}
	else if (argv[1][0] == '-')
	{
		if (!(path = get_env_value("OLDPWD", *env)))
			return (print_error("OLDPWD not set", argv));
		ft_printf("%s\n", path);
	}
	else
		path = argv[1];
	return (change_wdir(path, argv, env));
}
