/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <vgrankul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 11:28:19 by vgrankul          #+#    #+#             */
/*   Updated: 2020/09/16 15:19:07 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/21sh.h"

int		ft_echo(char **argv)
{
	int i;

	i = 1;
	while (argv[i] != NULL)
	{
		ft_printf("%s", argv[i]);
		if (argv[i + 1] != NULL)
			ft_printf(" ");
		i++;
	}
	ft_printf("\n");
	return (0);
}
