/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichinos <$yichinos@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 16:23:31 by ynishimu          #+#    #+#             */
/*   Updated: 2023/06/27 10:28:50 by yichinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/calculate.h"

//return rgb color
t_color	calculate_shade_color(t_scene *scene, double diffuse, t_color color)
{
	t_color	extracted_color;

	extracted_color = color;
	extracted_color.r = clamp((int)((scene->ambient.ratio + diffuse) * \
			extracted_color.r), 0, 255);
	extracted_color.g = clamp((int)((scene->ambient.ratio + diffuse) * \
			extracted_color.g), 0, 255);
	extracted_color.b = clamp((int)((scene->ambient.ratio + diffuse) * \
			extracted_color.b), 0, 255);
	return (extracted_color);
}
