/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichinos <yichinos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 16:23:31 by ynishimu          #+#    #+#             */
/*   Updated: 2023/06/03 15:32:47 by yichinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

int	parse_vector3(char *str, t_vector3 *vector)
{
	char	**split;

	split = ft_split(str, ',');
	if (!split || !split[0] || !split[1] || !split[2] || split[3]
		|| set_atod(split[0], &vector->x)
		|| set_atod(split[1], &vector->y)
		|| set_atod(split[2], &vector->z))
		return (1);
	return (0);
}
