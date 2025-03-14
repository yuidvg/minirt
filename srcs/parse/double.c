/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichinos <yichinos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 16:23:31 by ynishimu          #+#    #+#             */
/*   Updated: 2023/06/13 18:52:25 by yichinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/calculate.h"

static double	get_sign(char c)
{
	if (c == '-')
		return (-1);
	return (1);
}

static int	insert_integer(double *num, char *str, size_t *i)
{
	while (str[*i] && str[*i] != '.')
	{
		if (!ft_isdigit(str[*i]))
			return (1);
		*num = *num * 10 + str[*i] - '0';
		if (*num != 0 && (!isfinite(*num) || !isnormal(*num)))
			return (1);
		(*i)++;
	}
	return (0);
}

static int	insert_fraction(double *num, char *fractions)
{
	size_t	i;
	double	digit;

	digit = 10;
	i = 0;
	while (fractions[i])
	{
		if (!ft_isdigit(fractions[i]))
			return (1);
		*num += (fractions[i] - '0') / digit;
		if (*num != 0 && (isfinite(*num) == 0 || isnormal(*num) == 0))
			return (1);
		i++;
		digit *= 10;
	}
	return (0);
}

int	set_atod(char *str, double *num)
{
	size_t	i;
	double	sign;

	i = 0;
	*num = 0;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
		sign = get_sign(str[i++]);
	if (insert_integer(num, str, &i))
		return (1);
	if (str[i] && insert_fraction(num, str + i + 1))
		return (1);
	*num *= sign;
	return (0);
}
