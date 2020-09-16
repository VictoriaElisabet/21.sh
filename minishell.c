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

void	set_prt_str(char **prt_str, char ch[2])
{
	char	*tmp;

	if ((tmp = ft_strjoin(*prt_str, ch)))
	{
		free(*prt_str);
		*prt_str = tmp;
	}
}

char	*read_prompt(char *prompt)
{
	int		ret;
	char	ch[2];
	char	*prt_str;

	prt_str = NULL;
	ft_printf("%s", prompt);
	while ((ret = read(0, &ch, 1)) > 0)
	{
		ch[ret] = '\0';
		if (prt_str == NULL)
			if (!(prt_str = ft_strnew(0)))
				return (NULL);
		if ((int)ch[0] == EOF || ch[0] == '\n')
		{
			set_prt_str(&prt_str, ch);
			return (prt_str);
		}
		set_prt_str(&prt_str, ch);
	}
	if (ret < 0)
		return (NULL);
	return (prt_str);
}

int		main(void)
{
	extern char	**environ;
	//char		*prt_str;
	char		**env;
	//t_command	**commands;
	int			status;
	t_sh		*sh;

	status = 0;
	env = copy_env(environ);
	sh = (t_sh*)malloc(sizeof(t_sh));
	sh->in = (t_in*)malloc(sizeof(t_in));
	ft_validate_term();
	tcgetattr(STDIN_FILENO, &sh->orig);
	status = ft_sh(sh, env);
	/*while (1)
	{
		prt_str = read_prompt("$> ");
		if (prt_str != NULL)
		{
			commands = create_command_list(prt_str, env);
			if (commands != NULL)
				status = handle_command_list(commands, &env);
		}
	}*/
	destroy_arr(env);
	return (status);
}
