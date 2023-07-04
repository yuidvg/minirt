/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichinos <$yichinos@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 16:23:31 by ynishimu          #+#    #+#             */
/*   Updated: 2023/07/01 12:39:31 by yichinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/calculate.h"

static void	add_thickness(t_ray *intersection)
{
	intersection->pos = add_vecs(intersection->pos,
			scl_vec(intersection->dir, 0.0001));
}

t_ray	get_1st_intersection(t_object *object, t_ray *camera_ray,
t_color *color)
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
	add_thickness(&nearest_intersection);
	return (nearest_intersection);
}

t_ray	get_ray_toward_light(t_light *light, t_ray intersection)
{
	t_ray	ray_toward_light;

	ray_toward_light.dir = norm_vec(sub_vecs(light->pos,
				intersection.pos));
	ray_toward_light.pos = intersection.pos;
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
	if (magn_vec(intersection_with_other_object.dir) == 0 || magn_vec(sub_vecs(
				intersection_with_other_object.pos, ray_toward_light->pos))
		> magn_vec(sub_vecs(scene->light.pos, ray_toward_light->pos)))
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
	intersection
		= get_1st_intersection(scene->objects, &camera_ray, &object_color);
	if (magn_vec(intersection.dir) == 0)
		return ((t_color){0, 0, 0});
	ray_toward_light = get_ray_toward_light(&scene->light, intersection);
	diffused_light
		= get_diffused_light(scene, &intersection, &ray_toward_light);
	return (clamp_color(add_colors(
			scale_color(scene->ambient.color, scene->ambient.ratio),
			scale_color(object_color, diffused_light))));
}
