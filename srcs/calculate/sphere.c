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
	t_color	direct_color;
	double	direct_intensity;
	int		color;

	extracted_color = extract_color_components(scene->objects->color);
	direct_intensity = diffuse * scene->light.blightness;
	direct_color.r = (int)(direct_intensity * extracted_color.r);
	direct_color.g = (int)(direct_intensity * extracted_color.g);
	direct_color.b = (int)(direct_intensity * extracted_color.b);
	shade_color.r = clamp((int)(scene->ambient.ratio * extracted_color.r
				+ diffuse * extracted_color.r + direct_color.r), 0, 255);
	shade_color.g = clamp((int)(scene->ambient.ratio * extracted_color.r
				+ diffuse * extracted_color.g + direct_color.g), 0, 255);
	shade_color.b = clamp((int)(scene->ambient.ratio * extracted_color.b
				+ diffuse * extracted_color.b + direct_color.b), 0, 255);
	color = (shade_color.r << 16) | (shade_color.g << 8) | shade_color.b;
	return (color);
}

double	process_intersection(t_scene *scene, t_vector3 ray_direction, double t)
{
	t_vector3	intersection_point;
	t_vector3	normal_vector;
	t_vector3	light_vector;
	double		diffuse_intensity;

	intersection_point = (t_vector3){
		scene->camera.position.x + ray_direction.x * t,
		scene->camera.position.y + ray_direction.y * t,
		scene->camera.position.z + ray_direction.z * t};
	normal_vector = normalize(subtract_vectors(intersection_point,
				scene->objects->position));
	light_vector = normalize(subtract_vectors(scene->light.position,
				intersection_point));
	diffuse_intensity = inner_product(normal_vector, light_vector);
	diffuse_intensity = clamp(diffuse_intensity, 0.0, 1.0);
	return (diffuse_intensity);
}

void	set_sphere_color(t_scene *scene, int x, int y, double diffuse)
{
	int	color;

	color = calculate_shade_color(scene, diffuse);
	mlx_pixel_put(scene->mlx.ptr, scene->mlx.window, x, y, color);
}

void	render_sphere(t_scene *scene, int x, int y)
{
	t_vector3	ray_direction;
	double		discriminant;
	double		t;
	double		a;
	double		b;

	ray_direction = calculate_ray_direction(x, y);
	discriminant = calculate_discriminant(ray_direction,
			scene->camera.position, scene->objects->position,
			scene->objects->diameter);
	a = inner_product(ray_direction, ray_direction);
	b = 2 * inner_product(ray_direction,
			subtract_vectors(scene->camera.position,
				(scene->objects)->position));
	if (discriminant >= 0)
	{
		t = (-b - sqrt(discriminant)) / (2 * a);
		set_sphere_color(scene, x, y,
			process_intersection(scene, ray_direction, t));
	}
}
