/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichinos <$yichinos@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 16:23:31 by ynishimu          #+#    #+#             */
/*   Updated: 2023/06/27 11:53:46 by yichinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/calculate.h"

t_color	add_colors(t_color color1, t_color color2)
{
	t_color	color;

	color.r = color1.r + color2.r;
	color.g = color1.g + color2.g;
	color.b = color1.b + color2.b;
	return (color);
}

t_color	scale_color(t_color color, double scale)
{
	t_color	new_color;

	new_color.r = color.r * scale;
	new_color.g = color.g * scale;
	new_color.b = color.b * scale;
	return (new_color);
}
