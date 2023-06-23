/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichinos <$yichinos@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 16:23:31 by ynishimu          #+#    #+#             */
/*   Updated: 2023/06/23 20:30:42 by yichinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	convert_color_to_int(t_color color)
{
	int	rgb;

	rgb = (color.r << 16) | (color.g << 8) | color.b;
	return (rgb);
}

t_ray	get_1st_intersection(t_object *object, t_ray *camera_ray)
{
	t_ray	intersection;
	t_ray	nearest_intersection;
	double	nearest_distance;
	double	distance;

	nearest_distance = INFINITY;
	nearest_intersection = (t_ray){(t_vector3){0, 0, 0}, (t_vector3){0, 0, 0}};
	while (object)
	{
		intersection = object->get_intersection(&(t_){object, camera_ray});
		distance = magn_vec(sub_vecs(intersection.pos,
					camera_ray->pos));
		if (distance < nearest_distance)
		{
			nearest_distance = distance;
			nearest_intersection = intersection;

		}
		object = object->next;
	}
	return (nearest_intersection);
}

t_vector3	get_light_vector(t_scene *scene, t_ray intersection)
{
	t_vector3	light_vector;

	light_vector = norm_vec(sub_vecs(scene->light.pos,
				intersection.pos));
	return (light_vector);
}

t_color	type_check(t_object *object, t_ray intersection)
{
	if (intersection.dir.x == 0 && intersection.dir.y == 1
		&& intersection.dir.z == 0)
		return ((t_color){255, 255, 255});
	else
		return (object->color);
}

t_ray get_intersection_to_light(t_vector3 intersection, t_vector3 light_position)
{
	t_ray intersection_to_light;
	intersection_to_light.pos = intersection;
	intersection_to_light.dir = norm_vec(sub_vecs(light_position, intersection));
	return (intersection_to_light);
}

t_color	get_color(t_scene *scene, t_ray camera_ray)
{
	t_ray		intersection;
	t_ray		intersection_other_object;
	t_ray		intersection_tmp;
	t_vector3	light_vector;
	double		diffuse;
	t_color		tmp;

	diffuse = 0;
	intersection = get_1st_intersection(scene->objects, &camera_ray);
	if (magn_vec(intersection.dir) == 0)
		return ((t_color){100, 149, 237});
	intersection_tmp = get_intersection_to_light(intersection.pos, scene->light.pos);
	intersection_other_object = get_1st_intersection(scene->objects,
			&intersection_tmp);
	tmp = type_check(scene->objects, intersection);
	if (magn_vec(intersection_other_object.dir) == 0)
	{
		light_vector = get_light_vector(scene, intersection);
		diffuse = dot_vecs(intersection.dir, light_vector);
		diffuse = clamp(diffuse, 0.0, 1.0);
	}
	return (calculate_shade_color(scene, diffuse, tmp));
}

t_ray	get_camera_ray(int x, int y, t_camera *camera)
{
	t_ray	camera_ray;

	camera_ray.pos = camera->pos;
	camera_ray.dir.x = x - WIDTH / 2;
	camera_ray.dir.y = y - HEIGHT / 2;
	camera_ray.dir.z = -(WIDTH / (2.0 * tan(camera->fov / 2.0)));
	camera_ray.dir = norm_vec(camera_ray.dir);
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
	mlx_put_image_to_window(scene->mlx.ptr, scene->mlx.window, scene->mlx.image.ptr, 0, 0);
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
