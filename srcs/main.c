/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichinos <yichinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 16:23:31 by ynishimu          #+#    #+#             */
/*   Updated: 2023/06/26 17:55:17 by yichinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	convert_color_to_int(t_color color)
{
	int	rgb;

	rgb = (color.r << 16) | (color.g << 8) | color.b;
	return (rgb);
}

t_intersection	get_1st_intersection(t_object *object, t_ray *camera_ray)
{
	t_ray	point;
	t_ray	nearest_point;
	t_color	color;
	double	nearest_distance;
	double	distance;

	nearest_distance = INFINITY;
	nearest_point = (t_ray){(t_vector3){0, 0, 0}, (t_vector3){0, 0, 0}};
	while (object)
	{
		point = object->get_inter_point(&(t_){object, camera_ray});
		distance = magn_vec(sub_vecs(point.pos,
					camera_ray->pos));
		if (distance < nearest_distance)
		{
			nearest_distance = distance;
			nearest_point = point;
			color = object->color;
		}
		object = object->next;
	}
	return ((t_intersection){nearest_point, color});
}

t_vector3	get_light_vector(t_scene *scene, t_ray intersection)
{
	t_vector3	light_vector;

	light_vector = norm_vec(sub_vecs(scene->light.pos,
				intersection.pos));
	return (light_vector);
}

t_ray	get_shadow_ray(t_vector3 intersection,
			t_vector3 light_position)
{
	t_ray	intersection_to_light;

	intersection_to_light.pos = intersection;
	intersection_to_light.dir = norm_vec(sub_vecs(light_position,
				intersection));
	return (intersection_to_light);
}

t_ray	*converttoray(t_vector3 position, t_vector3 direction)
{
	t_ray	*ray;

	ray = NULL;
	ray->pos = position;
	ray->dir = direction;
	return (ray);
}

t_color	get_color(t_scene *scene, t_ray camera_ray)
{
	t_intersection	intersection;
	t_intersection	intersection_other_object;
	t_vector3		light_vector;
	t_ray			shadow_ray;
	double			diffuse;

	diffuse = 0;
	intersection = get_1st_intersection(scene->objects, &camera_ray);
	if (magn_vec(intersection.point.dir) == 0)
		return ((t_color){0, 0, 0});
	light_vector = get_light_vector(scene, intersection.point);
	shadow_ray = get_shadow_ray(intersection.point.pos, light_vector);
	intersection_other_object = get_1st_intersection(scene->objects,
			converttoray(intersection.point.pos, light_vector));
	if (magn_vec(intersection_other_object.point.dir) == 0)
	{
		diffuse = dot_vecs(intersection.point.dir, light_vector);
		diffuse = clamp(diffuse, 0.0, 1.0);
	}
	return (calculate_shade_color(scene, diffuse));
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
