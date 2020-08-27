/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 13:49:19 by vgrankul          #+#    #+#             */
/*   Updated: 2019/11/05 14:31:57 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int res;
	int i;
	int negative;

	i = 0;
	res = 0;
	negative = 1;
	while (str[i] == '\v' || str[i] == '\r' || str[i] == '\f' ||
			str[i] == '\n' || str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			negative = -1;
		i++;
	}
	while (str[i] && str[i] <= 57 && str[i] >= 48)
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * negative);
}
