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

#include "../includes/main.h"

void render_plane(t_scene *scene, int x, int y, t_vector3 ray_direction, t_vector3 ray_origin)
{
	t_vector3 plane_to_ray = subtract_vectors(ray_origin, scene->objects->next.position);
	double denominator;
	double t;
	t_vector3 intersection_point;
	t_vector3 plane_normal;
	double intersection_dot_normal;
	t_vector3 shadow_ray_origin;
	t_vector3 shadow_ray_direction;
	double shadow_t;
	int color;

	denominator = inner_product(scene.plane.normal, ray_direction);
	if (denominator != 0)
	{
		t = inner_product(scene.plane.normal, plane_to_ray) / denominator;
		if (t >= 0)
		{
			intersection_point = (t_vector3){
				ray_origin.x + ray_direction.x * t,
				ray_origin.y + ray_direction.y * t,
				ray_origin.z + ray_direction.z * t};
			plane_normal = scene.plane.normal;
			intersection_dot_normal = inner_product(ray_direction, plane_normal);
			if (intersection_dot_normal <= 0)
			{
				// 床に当たった場合、影の判定
				shadow_ray_origin = add_vectors(intersection_point, scale_vector(plane_normal, 0.001));
				shadow_ray_direction = subtract_vectors(scene.light, shadow_ray_origin);
				shadow_t = inner_product(normalize(scene.plane.normal), subtract_vectors(scene.plane.position, shadow_ray_origin)) / inner_product(normalize(scene.plane.normal), shadow_ray_direction);
				if (shadow_t > 0 && shadow_t < 1)
				{
					// 光源からの光が遮られている場合は床に黒の影を設定
					mlx_pixel_put(mlx, window, x, y, 0x000000);
					return;
				}
				color = scene.plane.color;
				mlx_pixel_put(mlx, window, x, y, color);
			}
		}
	}
}

void render_sphere(, int x, int y)
{
	double ray_dir_x;
	double ray_dir_y;
	double ray_dir_z;
	t_vector3 ray_direction;
	t_vector3 ray_origin;
	t_vector3 sphere_to_ray;
	double a;
	double b;
	double c;
	double discriminant;
	double t;
	t_vector3 intersection_point;
	t_vector3 normal;
	t_vector3 light_direction;
	double diffuse_intensity;
	t_vector3 shadow_ray_origin;
	t_vector3 shadow_ray_direction;
	double shadow_t;
	double ambient;
	double diffuse;
	int r;
	int g;
	int blue;
	int shade_r;
	int shade_g;
	int shade_b;
	int color;

	scene->camera.position = (t_vector3){0, -2, 0};
	ray_dir_x = (x - WIDTH / 2) / (WIDTH / 2.0);
	ray_dir_y = -(y - HEIGHT / 2) / (HEIGHT / 2.0);
	ray_dir_z = 1.0;
	ray_direction = normalize((t_vector3){ray_dir_x, ray_dir_y, ray_dir_z});
	ray_origin = (scene->camera).position;
	sphere_to_ray = subtract_vectors(ray_origin, (scene->objects)->position);
	a = inner_product(ray_direction, ray_direction);
	b = 2 * inner_product(ray_direction, sphere_to_ray);
	c = inner_product(sphere_to_ray, sphere_to_ray) - ((scene->objects->diameter * scene->objects->diameter) / 4.0);
	discriminant = b * b - 4 * a * c;
	if (discriminant >= 0)
	{
		t = (-b - sqrt(discriminant)) / (2 * a);
		intersection_point = (t_vector3){
			ray_origin.x + ray_direction.x * t,
			ray_origin.y + ray_direction.y * t,
			ray_origin.z + ray_direction.z * t};
		normal = normalize(subtract_vectors(intersection_point, scene->objects->position));
		light_direction = normalize(subtract_vectors((scene->light).position, intersection_point));
		diffuse_intensity = inner_product(normal, light_direction);
		diffuse_intensity = clamp(diffuse_intensity, 0.0, 1.0);
		shadow_ray_origin = add_vectors(intersection_point, scale_vector(normal, 0.001));
		shadow_ray_direction = subtract_vectors(scene->light.position, shadow_ray_origin);
		if (shadow_t > 0 && shadow_t < 1)
		{
			mlx_pixel_put(scene->mlx.ptr, scene->mlx.window, x, y, 0x000000);
			return;
		}
		ambient = 0.1;
		diffuse = diffuse_intensity;
		r = (scene->objects)->color.red >> 16 & 0xFF;
		g = (scene->objects)->color.green >> 8 & 0xFF;
		blue = (scene->objects)->color.blue & 0xFF;
		shade_r = (int)(ambient * r + diffuse * r);
		shade_g = (int)(ambient * g + diffuse * g);
		shade_b = (int)(ambient * blue + diffuse * blue);
		shade_r = (shade_r > 255) ? 255 : shade_r;
		shade_g = (shade_g > 255) ? 255 : shade_g;
		shade_b = (shade_b > 255) ? 255 : shade_b;
		color = (shade_r << 16) | (shade_g << 8) | shade_b;
		mlx_pixel_put(scene->mlx.ptr, scene->mlx.window, x, y, color);
	}
}


void	render_scene(t_scene *scene)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			render_sphere(scene, x, y);
			render_plane(scene, x, y);
			x++;
		}
		y++;
	}
}


int main(int argc, char **argv)
{
	void		*mlx;
	void		*window;
	t_scene		scene;

	if (argc != 2)
		gfree_exit(0, "Error\nUsage: %s [*.rt]\n", argv[0]);
	init_mlx(&scene);
	init_scene(argv[1], &scene);
	scene.objects->position = (t_vector3){0, -2, -5}; // 球の位置を調整（y座標を-2に設定）
	scene.light = (t_vector3){5, -5, -5};
	scene.objects->type = SPHERE;
	scene.objects->radius = 2.0;
	scene.objects->color = 0x00FF00;
	scene.plane.position = (t_vector3){0, 1, -2}; // 地面の位置を調整（y座標を0に設定）
	scene.plane.normal = (t_vector3){0, 1, 0};
	scene.plane.color = (t_color){0x00, 0x00, 0xFF};
	render_scene(scene, mlx, window);
	mlx_loop(mlx);
	gfree_exit(0, NULL);
}
