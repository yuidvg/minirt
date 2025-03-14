/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichinos <yichinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 16:23:31 by ynishimu          #+#    #+#             */
/*   Updated: 2023/06/28 17:12:34 by yichinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/calculate.h"

static int	within_height(t_object *cylinder, t_ray *camera_ray, double t)
{
	double	intersection_from_cylinder_pos;

	intersection_from_cylinder_pos = magn_vec(sub_vecs(
				add_vecs(camera_ray->pos, scl_vec(camera_ray->dir, t)),
				cylinder->pos));
	if (intersection_from_cylinder_pos * intersection_from_cylinder_pos
		<= cylinder->rad * cylinder->rad
		+ (cylinder->height / 2) * (cylinder->height / 2))
		return (1);
	return (0);
}

void	get_dt(t_object *cylinder, t_ray *camera_ray, double *d, double t[2])
{
	t_vector3	p;
	t_vector3	q;
	double		a;
	double		b;
	double		c;

	p = sub_vecs(camera_ray->dir,
			(scl_vec(cylinder->dir,
					dot_vecs(camera_ray->dir, cylinder->dir))));
	q = sub_vecs(sub_vecs(camera_ray->pos, cylinder->pos),
			scl_vec(cylinder->dir, dot_vecs(
					sub_vecs(camera_ray->pos, cylinder->pos),
					cylinder->dir)));
	a = dot_vecs(p, p);
	b = 2 * dot_vecs(p, q);
	c = dot_vecs(q, q) - cylinder->rad * cylinder->rad;
	*d = b * b - 4 * a * c;
	if (*d >= 0)
	{
		t[0] = (-b - sqrt(*d)) / a / 2;
		t[1] = (-b + sqrt(*d)) / a / 2;
	}
}

t_ray	get_intersection_cylinder(t_ *data)
{
	t_object	*cylinder;
	t_ray		*camera_ray;
	double		d;
	double		t[2];
	t_ray		intersection;

	cylinder = data->this;
	camera_ray = data->camera_ray;
	get_dt(cylinder, camera_ray, &d, t);
	if (d < 0)
		return ((t_ray){.pos = {0, 0, 0}, .dir = {0, 0, 0}});
	if (t[0] >= 0 && within_height(cylinder, camera_ray, t[0]))
		intersection.pos
			= add_vecs(camera_ray->pos, scl_vec(camera_ray->dir, t[0]));
	else if (t[1] >= 0 && within_height(cylinder, camera_ray, t[1]))
		intersection.pos
			= add_vecs(camera_ray->pos, scl_vec(camera_ray->dir, t[1]));
	else
		return ((t_ray){.pos = {0}, .dir = {0}});
	intersection.dir = norm_vec(sub_vecs(sub_vecs(intersection.pos,
					cylinder->pos), scl_vec(cylinder->dir,
					dot_vecs(sub_vecs(intersection.pos, cylinder->pos),
						cylinder->dir))));
	switch_intersection_dir(&intersection, camera_ray->pos);
	return (intersection);
}
