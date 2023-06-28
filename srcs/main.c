/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichinos <yichinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 16:23:31 by ynishimu          #+#    #+#             */
/*   Updated: 2023/06/28 17:09:51 by yichinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	convert_color_to_int(t_color color)
{
	int	rgb;

	rgb = (color.r << 16) | (color.g << 8) | color.b;
	return (rgb);
}

t_ray	get_1st_intersection(t_object *object, t_ray *camera_ray, t_color *color)
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
		if (magn_vec(intersection.dir) != 0 && distance < nearest_distance)
		{
			nearest_distance = distance;
			nearest_intersection = intersection;
			if (color)
				*color = object->color;
		}
		object = object->next;
	}
	return (nearest_intersection);
}

t_ray	get_ray_toward_light(t_scene *scene, t_ray intersection)
{
	t_ray	ray_toward_light;

	ray_toward_light.dir = norm_vec(sub_vecs(scene->light.pos,
				intersection.pos));
	ray_toward_light.pos = add_vecs(intersection.pos,
			scl_vec(ray_toward_light.dir, 0.0001));
	return (ray_toward_light);
}

double	get_diffused_light(t_scene *scene, t_ray *intersection,
t_ray *ray_toward_light)
{
	t_ray		intersection_with_other_object;
	double		diffused_light;

	diffused_light = 0;
	intersection_with_other_object
		= get_1st_intersection(scene->objects, ray_toward_light, NULL);
	if (magn_vec(intersection_with_other_object.dir) == 0 ||
			magn_vec(sub_vecs(scene->light.pos, intersection->pos))
			< magn_vec(sub_vecs(intersection_with_other_object.pos,
					intersection->pos)))
	{
		diffused_light = dot_vecs(intersection->dir, ray_toward_light->dir)
			* scene->light.blightness * DIFFUSE_RATIO;
		diffused_light = clamp(diffused_light, 0.0, 1.0);
	}
	return (diffused_light);
}

t_color	get_color(t_scene *scene, t_ray camera_ray)
{
	t_ray		intersection;
	t_color		object_color;
	t_ray		ray_toward_light;
	double		diffused_light;

	diffused_light = 0;
	intersection = get_1st_intersection(scene->objects, &camera_ray, &object_color);
	if (magn_vec(intersection.dir) == 0)
		return ((t_color){0, 0, 0});
	ray_toward_light = get_ray_toward_light(scene, intersection);
	diffused_light = get_diffused_light(scene, &intersection, &ray_toward_light);
	return (add_colors(
			scale_color(scene->ambient.color, scene->ambient.ratio),
			scale_color(object_color, diffused_light)));
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
