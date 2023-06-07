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

int	parse_color(char *str, t_color *color)
{
	char	**rgb;

	rgb = ft_split(str, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
		return (1);
	if (set_atoi(rgb[0], &color->r) || set_atoi(rgb[1], &color->g)
		|| set_atoi(rgb[2], &color->b)
		|| !(0 <= color->r && color->r <= 255)
		|| !(0 <= color->g && color->g <= 255)
		|| !(0 <= color->b && color->b <= 255))
		return (1);
	return (0);
}
