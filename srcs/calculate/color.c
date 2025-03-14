/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichinos <$yichinos@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 16:23:31 by ynishimu          #+#    #+#             */
/*   Updated: 2023/07/01 12:39:17 by yichinos         ###   ########.fr       */
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

int	color_to_int(t_color color)
{
	int	rgb;

	rgb = (color.r << 16) | (color.g << 8) | color.b;
	return (rgb);
}

t_color	clamp_color(t_color color)
{
	t_color	clamped_color;

	clamped_color.r = clamp(color.r, 0, 255);
	clamped_color.g = clamp(color.g, 0, 255);
	clamped_color.b = clamp(color.b, 0, 255);
	return (clamped_color);
}
