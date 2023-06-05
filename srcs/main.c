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

// void render_plane(t_scene *scene, int x, int y)
// {
// 	t_vector3	plane_to_ray = subtract_vectors(ray_origin, scene->objects->next.position);
// 	double		denominator;
// 	double		t;
// 	t_vector3 intersection_point;
// 	t_vector3 plane_normal;
// 	double intersection_dot_normal;
// 	t_vector3 shadow_ray_origin;
// 	t_vector3 shadow_ray_direction;
// 	double shadow_t;
// 	int color;

// 	denominator = inner_product(scene.plane.normal, ray_direction);
// 	if (denominator != 0)
// 	{
// 		t = inner_product(scene.plane.normal, plane_to_ray) / denominator;
// 		if (t >= 0)
// 		{
// 			intersection_point = (t_vector3){
// 				ray_origin.x + ray_direction.x * t,
// 				ray_origin.y + ray_direction.y * t,
// 				ray_origin.z + ray_direction.z * t};
// 			plane_normal = scene.plane.normal;
// 			intersection_dot_normal = inner_product(ray_direction, plane_normal);
// 			if (intersection_dot_normal <= 0)
// 			{
// 				// 床に当たった場合、影の判定
// 				shadow_ray_origin = add_vectors(intersection_point, scale_vector(plane_normal, 0.001));
// 				shadow_ray_direction = subtract_vectors(scene.light, shadow_ray_origin);
// 				shadow_t = inner_product(normalize(scene.plane.normal), subtract_vectors(scene.plane.position, shadow_ray_origin)) / inner_product(normalize(scene.plane.normal), shadow_ray_direction);
// 				if (shadow_t > 0 && shadow_t < 1)
// 				{
// 					// 光源からの光が遮られている場合は床に黒の影を設定
// 					mlx_pixel_put(mlx, window, x, y, 0x000000);
// 					return;
// 				}
// 				color = scene.plane.color;
// 				mlx_pixel_put(scene->mlx.ptr, scene->mlx.window, x, y, color);
// 			}
// 		}
// 	}
// }

double	process_intersection(t_scene *scene, t_vector3 ray_direction, double t)
{
	t_vector3	intersection_point;
	t_vector3	normal;
	t_vector3	light_direction;
	double		diffuse_intensity;
	double		direct_light_intensity;

	intersection_point = (t_vector3){
		scene->camera.position.x + ray_direction.x * t,
		scene->camera.position.y + ray_direction.y * t,
		scene->camera.position.z + ray_direction.z * t};
	normal = normalize(subtract_vectors(intersection_point,
				scene->objects->position));
	diffuse_intensity = inner_product(normal, light_direction);
	diffuse_intensity = clamp(diffuse_intensity, 0.0, 1.0);
	light_direction = normalize(subtract_vectors((scene->light).position,
				intersection_point));
	direct_light_intensity = inner_product(normal, light_direction);
	direct_light_intensity = clamp(diffuse_intensity, 0.0, 1.0);

	return (diffuse_intensity + direct_light_intensity);
}

void	set_objects_color(t_scene *scene, int x, int y, double diffuse)
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
		set_objects_color(scene, x, y,
			process_intersection(scene, ray_direction, t));
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
	scene.objects->type = SPHERE;
	scene.objects->diameter = 4.0;
	scene.objects->color.r = 50;
	scene.objects->color.g = 50;
	scene.objects->color.b = 50;
	scene.light.position = (t_vector3){5, -5, -5};
	scene.objects->position = (t_vector3){0, 0, -5};
	render_scene(&scene);
	mlx_loop(scene.mlx.ptr);
	gfree_exit(0, NULL);
}
