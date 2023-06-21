/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichinos <yichinos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 16:23:31 by ynishimu          #+#    #+#             */
/*   Updated: 2023/06/15 16:57:51 by yichinos         ###   ########.fr       */
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
	t = -(dot_vecs(s, plane->dir)
			/ dot_vecs(camera->dir, plane->dir));
	if (t > 0
		&& dot_vecs(camera->dir, plane->dir) < 0)
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
	d = (2 * dot_vecs(camera->dir, sub_vecs(camera->pos, sphere->pos)))
		* (2 * dot_vecs(camera->dir, sub_vecs(camera->pos, sphere->pos)))
		- 4 * (magn_vec(camera->dir) * magn_vec(camera->dir))
		* (magn_vec(sub_vecs(camera->pos, sphere->pos))
			* magn_vec(sub_vecs(camera->pos, sphere->pos))
			- sphere->rad * sphere->rad);
	t = (-2 * dot_vecs(camera->dir, sub_vecs(camera->pos, sphere->pos))
			- sqrt(d)) / (2 * magn_vec(camera->dir) * magn_vec(camera->dir));
	if (d >= 0 && t >= 0)
		return ((t_ray){
			add_vecs(camera->pos, scl_vec(camera->dir, t)),
			norm_vec(sub_vecs(add_vecs(camera->pos,
						scl_vec(camera->dir, t)), sphere->pos))});
	else
		return ((t_ray){.pos = {0}, .dir = {0}});
}

static int	within_height(t_object *cylinder, t_ray *camera_ray, double t)
{
	return (dot_vecs(
			sub_vecs(add_vecs(camera_ray->pos, scl_vec(camera_ray->dir, t)),
				cylinder->pos),
			sub_vecs(add_vecs(camera_ray->pos, scl_vec(camera_ray->dir, t)),
				cylinder->pos))
		<= cylinder->rad * cylinder->rad
		+ (cylinder->height / 2) * (cylinder->height / 2));
}

t_ray	get_intersection_cylinder(t_ *data)
{
	t_object	*cylinder;
	t_ray		*camera_ray;
	double		a;
	double		b;
	double		c;
	double		d;
	double		t;
	t_vector3	position;

	cylinder = data->this;
	camera_ray = data->camera_ray;
	a = dot_vecs(camera_ray->dir, camera_ray->dir)
		- dot_vecs(camera_ray->dir, cylinder->dir)
		* dot_vecs(camera_ray->dir, cylinder->dir)
		/ dot_vecs(cylinder->dir, cylinder->dir);
	b = dot_vecs(sub_vecs(cylinder->pos, camera_ray->pos), cylinder->dir)
		- dot_vecs(sub_vecs(cylinder->pos, camera_ray->pos), cylinder->dir)
		* dot_vecs(cylinder->dir, camera_ray->dir)
		/ dot_vecs(cylinder->dir, cylinder->dir);
	c = dot_vecs(sub_vecs(cylinder->pos, camera_ray->pos),
			sub_vecs(cylinder->pos, camera_ray->pos))
		- dot_vecs(sub_vecs(cylinder->pos, camera_ray->pos), cylinder->dir)
		* dot_vecs(sub_vecs(cylinder->pos, camera_ray->pos), cylinder->dir)
		/ dot_vecs(cylinder->dir, cylinder->dir)
		- cylinder->rad * cylinder->rad;
	d = b * b - a * c;
	t = (-b - sqrt(d)) / a;
	if (t > 0 && d >= 0 && within_height(cylinder, camera_ray, t))
	{
		position = add_vecs(camera_ray->pos, scl_vec(camera_ray->dir, t));
		return ((t_ray){.pos = position,
			.dir = norm_vec(sub_vecs(sub_vecs(position, cylinder->pos),
					scl_vec(cylinder->dir,
						dot_vecs(sub_vecs(position, cylinder->pos),
							cylinder->dir))))});
	}
	else if (t > 0 && d >= 0
		&& within_height(cylinder, camera_ray, t + sqrt(d) / a * 2))
	{
		position = add_vecs(camera_ray->pos, scl_vec(camera_ray->dir,
					t + sqrt(d) / a * 2));
		return ((t_ray){.pos = position,
			.dir = norm_vec(sub_vecs(sub_vecs(position, cylinder->pos),
					scl_vec(cylinder->dir,
						dot_vecs(sub_vecs(position, cylinder->pos),
							cylinder->dir))))});
	}
	else
		return ((t_ray){.pos = {0}, .dir = {0}});
}
