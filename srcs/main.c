/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ${USER} <${USER}@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 16:23:31 by ynishimu          #+#    #+#             */
/*   Updated: 2023/06/04 23:33:41 by ${USER}          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

t_color	plane_extract_color_components(t_color source_color)
{
	t_color	extracted_color;

	extracted_color.r = (source_color.r >> 16) & 0xFF;
	extracted_color.g = (source_color.g >> 8) & 0xFF;
	extracted_color.b = source_color.b & 0xFF;
	return (extracted_color);
}

int	plane_calculate_shade_color(t_scene *scene, double diffuse)
{
	t_color	extracted_color;
	t_color	shade_color;
	int		color;

	extracted_color = plane_extract_color_components
		(scene->objects->next->color);
	shade_color.r = clamp((int)(scene->ambient.ratio * extracted_color.r
				+ diffuse * (extracted_color.r / 255.0)), 0, 255);
	shade_color.g = clamp((int)(scene->ambient.ratio * extracted_color.g
				+ diffuse * (extracted_color.g / 255.0)), 0, 255);
	shade_color.b = clamp((int)(scene->ambient.ratio * extracted_color.b
				+ diffuse * (extracted_color.b / 255.0)), 0, 255);
	color = (shade_color.r << 16) | (shade_color.g << 8) | shade_color.b;
	return (color);
}

double	plane_process_intersection(t_scene *scene,
		t_vector3 ray_direction, double denominator)
{
	t_vector3	intersection_point;
	t_vector3	plane_normal;
	t_vector3	light_vector;
	double		diffuse_intensity;

	intersection_point = (t_vector3){
		scene->camera.position.x + ray_direction.x * denominator,
		scene->camera.position.y + ray_direction.y * denominator,
		scene->camera.position.z + ray_direction.z * denominator};
	plane_normal = normalize(scene->objects->next->position);
	light_vector = normalize(subtract_vectors(scene->light.position,
				intersection_point));
	diffuse_intensity = inner_product(plane_normal, light_vector);
	diffuse_intensity = clamp(diffuse_intensity, 0.0, 1.0);
	return (diffuse_intensity);
}

void	set_plane_color(t_scene *scene, int x, int y, double diffuse)
{
	int	color;

	color = plane_calculate_shade_color(scene, diffuse);
	mlx_pixel_put(scene->mlx.ptr, scene->mlx.window, x, y, color);
}

void	render_plane(t_scene *scene, int x, int y)
{
	t_vector3	ray_direction;
	t_vector3	plane_normal;
	double		denominator;
	double		diffuse;

	ray_direction = calculate_ray_direction(x, y);
	plane_normal = normalize(scene->objects->next->position);
	denominator = inner_product(plane_normal, ray_direction);
	if (denominator != 0)
	{
		if (denominator >= 0)
		{
			diffuse = clamp(denominator, 0.0, 1.0);
			set_plane_color(scene, x, y, diffuse);
		}
	}
}

void	render_scene(t_scene *scene)
{
	int			x;
	int			y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			render_plane(scene, x, y);
			render_sphere(scene, x, y);
			x++;
		}
		y++;
	}
}

int	main(void)
{

	t_scene	scene;

	init_mlx(&scene);
	scene.objects = (t_object *)malloc(sizeof(t_object));
	scene.objects->next = (t_object *)malloc(sizeof(t_object));
	scene.camera.position = (t_vector3){0, 0, -10};
	scene.objects->diameter = 4.0;
	scene.objects->color.r = 50;
	scene.objects->color.g = 50;
	scene.objects->color.b = 50;
	scene.objects->position = (t_vector3){0, 0, 0};
	scene.objects->next->position = (t_vector3){0, -3, 0};
	scene.objects->next->color.r = 255;
	scene.objects->next->color.g = 255;
	scene.objects->next->color.b = 255;
	scene.ambient.ratio = 0.3;
	scene.light.position = (t_vector3){-3, 5, -5};
	render_scene(&scene);
	mlx_loop(scene.mlx.ptr);
	gfree_exit(0, NULL);
}
