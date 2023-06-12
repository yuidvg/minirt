/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichinos <$yichinos@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 16:23:31 by ynishimu          #+#    #+#             */
/*   Updated: 2023/06/12 11:30:50 by yichinos         ###   ########.fr       */
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
	t_color	direct_color;
	double	direct_intensity;
	int		color;

	extracted_color = plane_extract_color_components
		(scene->objects->next->color);
	direct_intensity = diffuse * scene->light.blightness;
	direct_color.r = (int)(direct_intensity * extracted_color.r);
	direct_color.g = (int)(direct_intensity * extracted_color.g);
	direct_color.b = (int)(direct_intensity * extracted_color.b);
	shade_color.r = clamp((int)(scene->ambient.ratio * extracted_color.r
				+ diffuse * extracted_color.r + direct_color.r), 0, 255);
	shade_color.g = clamp((int)(scene->ambient.ratio * extracted_color.g
				+ diffuse * extracted_color.g + direct_color.g), 0, 255);
	shade_color.b = clamp((int)(scene->ambient.ratio * extracted_color.b
				+ diffuse * extracted_color.b + direct_color.b), 0, 255);
	color = (shade_color.r << 16) | (shade_color.g << 8) | shade_color.b;
	return (color);
}

double	plane_process_intersection(t_scene *scene,
		t_vector3 ray_direction, double t)
{
	t_vector3	intersection_point;
	t_vector3	plane_normal;
	t_vector3	light_vector;
	double		diffuse_intensity;

	intersection_point = (t_vector3){
		scene->camera.position.x + ray_direction.x * t,
		scene->camera.position.x + ray_direction.y * t,
		scene->camera.position.x + ray_direction.z * t};
	light_vector = normalize_vector(subtract_vectors(scene->light.position,
				intersection_point));
	diffuse_intensity = inner_product_vectors(scene->objects->orientation, light_vector);
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
	double		denominator;
	double		t;
	double		diffuse;

	ray_direction = calculate_ray_direction(x, y);
	denominator = inner_product_vectors(ray_direction, scene->objects->orientation);
	if (denominator != 0)
	{
		t = inner_product_vectors(ray_direction, scene->objects->orientation) / denominator;
		if (t >= 0)
		{
			diffuse = plane_process_intersection(scene, ray_direction, t);
			set_plane_color(scene, x, y, diffuse);
		}
	}
}

t_ray	get_1st_intersection(t_object *object, t_ray *camera_ray)
{
	t_ray	intersection;
	t_ray	nearest_intersection;
	double	nearest_t;

	nearest_t = INFINITY;
	while (object)
	{
		intersection = object->get_intersection(&(t_){object, camera_ray});
		if (magnitude_vector(subtract_vectors(intersection.position, camera_ray->position)) < nearest_t)
		{
			nearest_t = intersection.t;
			nearest_intersection = intersection;
		}
		object = object->next;
	}
	return (nearest_intersection);
}

t_vector3 get_light_vector(t_scene *scene, t_ray intersection)
{
	t_vector3	light_vector;

	light_vector = normalize_vector(subtract_vectors(scene->light.position,
				intersection.position));
	return (light_vector);
}

t_color	get_color(t_scene *scene, t_ray camera_ray)
{
	t_ray		intersection;
	t_vector3	light_vector;
	int			diffuse;

	intersection = get_1st_intersection(scene->objects, &camera_ray);
	light_vector = get_light_vector(scene, intersection);
	diffuse = inner_product_vectors(intersection.orientation, light_vector);
	diffuse = clamp(diffuse, 0.0, 1.0);
	scene->objects->color = calculate_shade_color(scene, diffuse);
	return (scene->objects->color);
}

t_ray	get_camera_ray(int x, int y, t_camera *camera)
{
	t_ray	camera_ray;

	camera_ray.position = camera->position;
	camera_ray.orientation.x = (x - WIDTH / 2) / (WIDTH / 2.0);
	camera_ray.orientation.y = -(y - HEIGHT / 2) / (HEIGHT / 2.0);
	camera_ray.orientation.z = WIDTH / (2.0 * tan(camera->fov / 2.0));
	camera_ray.orientation = normalize_vector(camera_ray.orientation);
	return (camera_ray);
}

void	render_scene(t_scene *scene)
{
	int			x;
	int			y;
	t_color		color;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			color = get_color(scene, get_camera_ray(x, y, &scene->camera));
			my_mlx_pixel_put(scene, x, y, convert_color_to_int(color));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(scene->mlx.ptr, scene->mlx.window, scene->mlx.img, 0, 0);
}

int	main(int argc, char **argv)
{
	t_scene	scene;

	if (argc != 2)
		gfree_exit(1, "Error\nInvalid number of arguments\n");
	init_mlx(&scene);
	init_scene(argv[1], &scene);
	render_scene(&scene);
	mlx_loop(scene.mlx.ptr);
	gfree_exit(0, NULL);
}
