/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ${USER} <${USER}@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 16:23:31 by ynishimu          #+#    #+#             */
/*   Updated: 2023/06/04 23:30:20 by ${USER}          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

int	set_color(char *str, t_color *color)
{
	char	**rgb;

	rgb = ft_split(str, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
		return (1);
	if (set_atod(rgb[0], &color->r) || set_atod(rgb[1], &color->g)
		|| set_atod(rgb[2], &color->b))
		return (1);
}

t_color	extract_color_components(t_color source_color)
{
	t_color	extracted_color;

	extracted_color.r = (source_color.r >> 16) & 0xFF;
	extracted_color.g = (source_color.g >> 8) & 0xFF;
	extracted_color.b = source_color.b & 0xFF;
	return (extracted_color);
}

//return rgb color
int	calculate_shade_color(t_scene *scene, double diffuse)
{
	t_color	extracted_color;
	t_color	shade_color;
	int		color;

	extracted_color = extract_color_components(scene->objects->color);
	shade_color.r = clamp((int)(scene->ambient.ratio
				* extracted_color.r + diffuse * extracted_color.r), 0, 255);
	shade_color.g = clamp((int)(scene->ambient.ratio
				* extracted_color.r + diffuse * extracted_color.g), 0, 255);
	shade_color.b = clamp((int)(scene->ambient.ratio
				* extracted_color.b + diffuse * extracted_color.b), 0, 255);
	color = (shade_color.r << 16) | (shade_color.g << 8) | shade_color.b;
	return (color);
}
