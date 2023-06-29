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

t_ray	get_intersection_plane(t_ *data)
{
	t_object	*plane;
	t_ray		*camera;
	double		t;
	t_vector3	s;
	t_ray		intersection;

	plane = data->this;
	camera = data->camera_ray;
	s = sub_vecs(camera->pos, plane->pos);
	t = -(dot_vecs(s, plane->dir)
			/ dot_vecs(camera->dir, plane->dir));
	if (t > 0)
	{
		intersection.pos
			= add_vecs(add_vecs(s, scl_vec(camera->dir, t)), plane->pos);
		intersection.dir = plane->dir;
		switch_intersection_dir(&intersection, camera->pos);
		return (intersection);
	}
	return ((t_ray){.pos = {0, 0, 0}, .dir = {0, 0, 0}});
}
