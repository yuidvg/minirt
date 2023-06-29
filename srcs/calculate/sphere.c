/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichinos <$yichinos@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 16:23:31 by ynishimu          #+#    #+#             */
/*   Updated: 2023/06/27 10:28:50 by yichinos         ###   ########.fr       */
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

static void	get_dt(t_object *sphere, t_ray *camera_ray, double *d, double t[2])
{
	*d = (2 * dot_vecs(camera_ray->dir, sub_vecs(camera_ray->pos, sphere->pos)))
		* (2 * dot_vecs(camera_ray->dir,
				sub_vecs(camera_ray->pos, sphere->pos)))
		- 4 * (magn_vec(camera_ray->dir) * magn_vec(camera_ray->dir))
		* (magn_vec(sub_vecs(camera_ray->pos, sphere->pos))
			* magn_vec(sub_vecs(camera_ray->pos, sphere->pos))
			- sphere->rad * sphere->rad);
	t[0] = (-2 * dot_vecs(camera_ray->dir,
				sub_vecs(camera_ray->pos, sphere->pos)) - sqrt(*d))
		/ (2 * magn_vec(camera_ray->dir) * magn_vec(camera_ray->dir));
	t[1] = (-2 * dot_vecs(camera_ray->dir,
				sub_vecs(camera_ray->pos, sphere->pos)) + sqrt(*d))
		/ (2 * magn_vec(camera_ray->dir) * magn_vec(camera_ray->dir));
}

t_ray	get_intersection_sphere(t_ *data)
{
	t_object	*sphere;
	t_ray		*camera;
	double		t[2];
	double		d;
	t_ray		intersection;

	sphere = data->this;
	camera = data->camera_ray;
	get_dt(sphere, camera, &d, t);
	if (d < 0)
		return ((t_ray){.pos = {0}, .dir = {0}});
	if (t[0] >= 0)
		intersection.pos
			= add_vecs(camera->pos, scl_vec(camera->dir, t[0]));
	else if (t[1] >= 0)
		intersection.pos
			= add_vecs(camera->pos, scl_vec(camera->dir, t[1]));
	else
		return ((t_ray){.pos = {0}, .dir = {0}});
	intersection.dir = norm_vec(sub_vecs(intersection.pos, sphere->pos));
	switch_intersection_dir(&intersection, camera->pos);
	return (intersection);
}
