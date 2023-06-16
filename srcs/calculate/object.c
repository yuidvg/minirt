/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichinos <yichinos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 16:23:31 by ynishimu          #+#    #+#             */
/*   Updated: 2023/06/13 18:20:00 by yichinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/calculate.h"

t_ray	get_intersection_plane(t_ *data)
{
	t_object	*plane;
	t_ray		*camera;
	double		t;
	t_vector3	s;

	plane = data->this;
	camera = data->camera_ray;
	s = sub_vecs(camera->pos, plane->pos);
	t = -(inpro_vec(s, plane->dir)
			/ inpro_vec(camera->dir, plane->dir));
	if (t > 0
		&& inpro_vec(camera->dir, plane->dir) < 0)
		return ((t_ray){add_vecs(add_vecs(s,
					scl_vec(camera->dir, t)), plane->pos),
			plane->dir});
	else if (t > 0)
		return ((t_ray){add_vecs(add_vecs(s,
					scl_vec(camera->dir, t)), plane->pos),
			scl_vec(plane->dir, -1)});
	return ((t_ray){.pos = {0, 0, 0}, .dir = {0, 0, 0}});
}

t_ray	get_intersection_sphere(t_ *data)
{
	t_object	*sphere;
	t_ray		*camera;
	double		t;
	double		d;

	sphere = data->this;
	camera = data->camera_ray;
	d = (2 * inpro_vec(camera->dir, sub_vecs(camera->pos, sphere->pos)))
		* (2 * inpro_vec(camera->dir, sub_vecs(camera->pos, sphere->pos)))
		- 4 * (magn_vec(camera->dir) * magn_vec(camera->dir))
		* (magn_vec(sub_vecs(camera->pos, sphere->pos))
			* magn_vec(sub_vecs(camera->pos, sphere->pos))
			- sphere->diameter * sphere->diameter);
	t = (-2 * inpro_vec(camera->dir, sub_vecs(camera->pos, sphere->pos))
			- sqrt(d)) / (2 * magn_vec(camera->dir) * magn_vec(camera->dir));
	if (d >= 0 && t >= 0)
		return ((t_ray){
			add_vecs(camera->pos, scl_vec(camera->dir, t)),
			sub_vecs(add_vecs(camera->pos, scl_vec(camera->dir, t)),
				sphere->pos)});
	else
		return ((t_ray){.pos = {0}, .dir = {0}});
}

t_ray	get_intersection_cylinder(t_ *data)
{
	t_object	*cylinder;
	t_ray		*camera;
	double		t;
	t_vector3	s;

	cylinder = data->this;
	camera = data->camera_ray;
	s = sub_vecs(camera->pos, cylinder->pos);
	t = inpro_vec(camera->dir, cylinder->dir)
		* inpro_vec(camera->dir, cylinder->dir)
		- inpro_vec(camera->dir, camera->dir)
		* (inpro_vec(s, s)
			- cylinder->diameter * cylinder->diameter);
	if (t < 0)
		return ((t_ray){.pos = {0}, .dir = {0}});
	t = (-inpro_vec(camera->dir, s) - sqrt(t))
		/ inpro_vec(camera->dir, camera->dir);
	if (t > 0)
		return ((t_ray){add_vecs(camera->pos,
				scl_vec(camera->dir, t)), s});
	return ((t_ray){.pos = {0}, .dir = {0}});
}
