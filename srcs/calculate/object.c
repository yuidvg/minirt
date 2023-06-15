/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichinos <yichinos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 16:23:31 by ynishimu          #+#    #+#             */
/*   Updated: 2023/06/15 15:00:42 by yichinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/calculate.h"

t_ray	get_intersection_plane(t_ *data)
{
	t_object	*plane;
	t_ray		*camera;
	double		t;
	t_vector3	s;
	t_vector3	n;
	t_vector3	d;

	plane = data->this;
	camera = data->camera_ray;
	n = plane->orientation;
	d = camera->orientation;
	s = subtract_vectors(camera->position, plane->position);
	t = -(inner_product_vectors(s, n)
			/ inner_product_vectors(d, n));
	if (t > 0
		&& inner_product_vectors(camera->orientation, plane->orientation) < 0)
	{
		return ((t_ray){add_vectors(add_vectors(s,
					scale_vector(camera->orientation, t)), plane->position),
			plane->orientation});
	}
	else if (t > 0)
	{
		return ((t_ray){add_vectors(add_vectors(s,
					scale_vector(camera->orientation, t)), plane->position),
			scale_vector(plane->orientation, -1)});
	}
	else
	{
		return ((t_ray){.position = {0, 0, 0}, .orientation = {0, 0, 0}});
	}
}

t_ray	get_intersection_sphere(t_ *data)
{
	t_object	*sphere;
	t_ray		*camera;
	double		t;
	t_vector3	s;

	sphere = data->this;
	camera = data->camera_ray;
	s = subtract_vectors(camera->position, sphere->position);
	t = inner_product_vectors(camera->orientation, s)
		* inner_product_vectors(camera->orientation, s)
		- inner_product_vectors(camera->orientation, camera->orientation)
		* (inner_product_vectors(s, s) - sphere->diameter * sphere->diameter);
	if (t < 0)
		return ((t_ray){.position = {0}, .orientation = {0}});
	t = (-inner_product_vectors(camera->orientation, s) - sqrt(t))
		/ inner_product_vectors(camera->orientation, camera->orientation);
	if (t > 0)
		return ((t_ray){add_vectors(camera->position,
				scale_vector(camera->orientation, t)), s});
	return ((t_ray){.position = {0}, .orientation = {0}});
}

t_ray	get_intersection_cylinder(t_ *data)
{
	t_object	*cylinder;
	t_ray		*camera;
	double		t;
	t_vector3	s;

	cylinder = data->this;
	camera = data->camera_ray;
	s = subtract_vectors(camera->position, cylinder->position);
	t = inner_product_vectors(camera->orientation, cylinder->orientation)
		* inner_product_vectors(camera->orientation, cylinder->orientation)
		- inner_product_vectors(camera->orientation, camera->orientation)
		* (inner_product_vectors(s, s)
			- cylinder->diameter * cylinder->diameter);
	if (t < 0)
		return ((t_ray){.position = {0}, .orientation = {0}});
	t = (-inner_product_vectors(camera->orientation, s) - sqrt(t))
		/ inner_product_vectors(camera->orientation, camera->orientation);
	if (t > 0)
		return ((t_ray){add_vectors(camera->position,
				scale_vector(camera->orientation, t)), s});
	return ((t_ray){.position = {0}, .orientation = {0}});
}
