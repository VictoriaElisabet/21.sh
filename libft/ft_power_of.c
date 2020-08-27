/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_power_of.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <vgrankul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 14:12:42 by vgrankul          #+#    #+#             */
/*   Updated: 2020/02/17 14:44:10 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long long	ft_power_of(int base, int exp)
{
	long double res;

	res = 1;
	base = (long long)base;
	exp = (long long)exp;
	while (exp > 0)
	{
		res = res * base;
		exp--;
	}
	return (res);
}
