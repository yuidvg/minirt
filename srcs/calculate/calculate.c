/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ${USER} <${USER}@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 16:23:31 by ynishimu          #+#    #+#             */
/*   Updated: 2023/06/04 16:33:37 by ${USER}          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/calculate.h"

t_vector3	calculate_ray_direction(int x, int y)
{
	t_vector3	ray_direction;
	double		ray_dir_x;
	double		ray_dir_y;
	double		ray_dir_z;

	ray_dir_x = (x - WIDTH / 2) / (WIDTH / 2.0);
	ray_dir_y = -(y - HEIGHT / 2) / (HEIGHT / 2.0);
	ray_dir_z = 1.0;
	ray_direction = norm_vec((t_vector3){ray_dir_x, ray_dir_y, ray_dir_z});
	return (ray_direction);
}

double	calculate_discriminant(t_vector3 ray_direction, t_vector3 ray_origin,
			t_vector3 object_position, double object_diameter)
{
	t_vector3	sphere_to_ray;
	double		a;
	double		b;
	double		c;
	double		discriminant;

	sphere_to_ray = sub_vecs(ray_origin, object_position);
	a = dot_vecs(ray_direction, ray_direction);
	b = 2 * dot_vecs(ray_direction, sphere_to_ray);
	c = dot_vecs(sphere_to_ray, sphere_to_ray)
		- ((object_diameter * object_diameter) / 4.0);
	discriminant = b * b - 4 * a * c;
	return (discriminant);
}

void	switch_intersection_dir(t_ray *intersection, t_vector3 ray_origin)
{
	t_vector3	from_intersection_to_origin;

	from_intersection_to_origin = sub_vecs(ray_origin, intersection->pos);
	if (dot_vecs(from_intersection_to_origin, intersection->dir) < 0)
		intersection->dir = scl_vec(intersection->dir, -1);
}
