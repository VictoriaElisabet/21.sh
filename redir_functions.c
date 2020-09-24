/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <vgrankul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 11:28:19 by vgrankul          #+#    #+#             */
/*   Updated: 2020/09/16 15:14:30 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/21sh.h"

void	set_redir_list(char redir[11][4])
{
	ft_strcpy(redir[0], "<");
	ft_strcpy(redir[1], "<<");
	ft_strcpy(redir[2], "<&");
	ft_strcpy(redir[3], "<&-");
	ft_strcpy(redir[4], "<<-");
	ft_strcpy(redir[5], "<>");
	ft_strcpy(redir[6], ">");
	ft_strcpy(redir[7], ">>");
	ft_strcpy(redir[8], ">&");
	ft_strcpy(redir[9], ">&-");
	ft_strcpy(redir[10], ">|");
}

int		is_redir_in(int r_type)
{
	if (r_type == L || r_type == LL || r_type == L_AND
	|| r_type == L_AND_H || r_type == LL_H)
		return (1);
	return (0);
}

int		is_redir_out(int r_type)
{
	if (r_type == G || r_type == GG || r_type == G_AND
	|| r_type == G_AND_H || r_type == CLOBBER)
		return (1);
	return (0);
}

int		get_redir(char *token)
{
	int		i;
	char	redir[11][4];

	i = 0;
	set_redir_list(redir);
	while (i < 11)
	{
		if (ft_strcmp(token, redir[i]) == 0)
			return (i);
		i++;
	}
	return (0);
}

int		print_redir_error(char *str)
{
	ft_printf("%s\n", str);
	return (-1);
}
