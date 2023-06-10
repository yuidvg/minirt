/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynishimu <ynishimu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 16:23:31 by ynishimu          #+#    #+#             */
/*   Updated: 2023/04/11 16:08:45 by ynishimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/calculate.h"

t_ray	get_intersection_plane(t_ *data)
{
	t_ray		intersection;
	t_object	*plane;
	t_ray		*camera;
	double		t;
	t_vector3	s;

	plane = data->this;
	camera = data->camera_ray;
	s = subtract_vectors(camera->position, plane->position);
	t = -(inner_product_vectors(s, plane->orientation)
			/ inner_product_vectors(camera->orientation, plane->orientation));
	if (t > 0
		&& inner_product_vectors(camera->orientation, plane->orientation) < 0)
		return ((t_ray){add_vectors(add_vectors(s,
					scale_vector(camera->orientation, t)), plane->position),
			plane->orientation});
	else if (t > 0)
		return ((t_ray){add_vectors(add_vectors(s,
					scale_vector(camera->orientation, t)), plane->position),
			scale_vector(plane->orientation, -1)});
	return ((t_ray){0});
}
