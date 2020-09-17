/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <vgrankul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 11:28:19 by vgrankul          #+#    #+#             */
/*   Updated: 2020/09/16 15:16:17 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"
#include "./includes/sh.h"

void	destroy_arr(char **arr)
{
	int i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int		main(void)
{
	extern char	**environ;
	char		**env;
	int			status;
	t_sh		*sh;

	status = 0;
	env = copy_env(environ);
	sh = (t_sh*)malloc(sizeof(t_sh));
	sh->in = (t_in*)malloc(sizeof(t_in));
	ft_validate_term();
	tcgetattr(STDIN_FILENO, &sh->orig);
	status = ft_sh(sh, env);
	destroy_arr(env);
	return (status);
}
