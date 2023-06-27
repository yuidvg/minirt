/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichinos <$yichinos@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 16:23:31 by ynishimu          #+#    #+#             */
/*   Updated: 2023/06/22 22:29:30 by yichinos         ###   ########.fr       */
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


// double	process_intersection(t_scene *scene, t_vector3 ray_direction, double t)
// {
// 	t_vector3	intersection_point;
// 	t_vector3	normal_vector;
// 	t_vector3	light_vector;
// 	double		diffuse_intensity;

// 	intersection_point = (t_vector3){
// 		scene->camera.pos.x + ray_direction.x * t,
// 		scene->camera.pos.y + ray_direction.y * t,
// 		scene->camera.pos.z + ray_direction.z * t};
// 	normal_vector = normalize(subtract_vectors(intersection_point,
// 				scene->objects->pos));
// 	light_vector = normalize(subtract_vectors(scene->light.pos,
// 				intersection_point));
// 	diffuse_intensity = inner_product(normal_vector, light_vector);
// 	diffuse_intensity = clamp(diffuse_intensity, 0.0, 1.0);
// 	return (diffuse_intensity);
// }

// void	set_sphere_color(t_scene *scene, int x, int y, double diffuse)
// {
// 	int	color;

// 	color = calculate_shade_color(scene, diffuse);
// 	mlx_pixel_put(scene->mlx.ptr, scene->mlx.window, x, y, color);
// }

// void	render_sphere(t_scene *scene, int x, int y)
// {
// 	t_vector3	ray_direction;
// 	double		discriminant;
// 	double		t;
// 	double		a;
// 	double		b;

// 	ray_direction = calculate_ray_direction(x, y);
// 	discriminant = calculate_discriminant(ray_direction,
// 			scene->camera.pos, scene->objects->pos,
// 			scene->objects->diameter);
// 	a = inner_product(ray_direction, ray_direction);
// 	b = 2 * inner_product(ray_direction,
// 			subtract_vectors(scene->camera.pos,
// 				(scene->objects)->pos));
// 	if (discriminant >= 0)
// 	{
// 		t = (-b - sqrt(discriminant)) / (2 * a);
// 		set_sphere_color(scene, x, y,
// 			process_intersection(scene, ray_direction, t));
// 	}
// }
