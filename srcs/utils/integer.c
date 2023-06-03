/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynishimu <ynishimu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 16:23:31 by ynishimu          #+#    #+#             */
/*   Updated: 2023/04/11 16:08:45 by ynishimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

int	will_overflow(long num, int next)
{
	if (num > INT_MAX / 10
		|| (num == INT_MAX / 10 && (long)next > INT_MAX % 10))
	{
		errno = ERANGE;
		return (1);
	}
	return (0);
}

int	will_underflow(long num, int next)
{
	num *= -1;
	next *= -1;
	if (num < INT_MIN / 10
		|| (num == INT_MIN / 10 && next < INT_MIN % 10))
	{
		errno = ERANGE;
		return (1);
	}
	return (0);
}

int	set_atoi(char *str, int *num)
{
	size_t	i;
	int		sign;

	i = 0;
	sign = 1;
	*num = 0;
	while (ft_strchr(ISSPACE, str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			sign = -1;
	}
	while ('0' <= str[i] && str[i] <= '9')
	{
		if (sign == 1 && will_overflow(num, str[i] - '0'))
			return ((int)LONG_MAX);
		if (sign == -1 && will_underflow(num, str[i] - '0'))
			return ((int)LONG_MIN);
		*num = (*num * 10) + (str[i++] - '0');
	}
}
