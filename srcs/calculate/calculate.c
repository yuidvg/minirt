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

t_vector3 calculate_ray_direction(int x, int y) 
{
	t_vector3	ray_direction;

	double ray_dir_x = (x - WIDTH / 2) / (WIDTH / 2.0);
	double ray_dir_y = -(y - HEIGHT / 2) / (HEIGHT / 2.0);
	double ray_dir_z = 1.0;
	ray_direction = normalize((t_vector3){ray_dir_x, ray_dir_y, ray_dir_z});
	return	(ray_direction);
}

double calculate_discriminant(t_vector3 ray_direction, t_vector3 ray_origin, t_vector3 object_position, double object_diameter)
{
	t_vector3	sphere_to_ray;
	double		a; 
	double		b;  
	double		c;
	double		discriminant;
	
	sphere_to_ray = subtract_vectors(ray_origin, object_position);
	a =	inner_product(ray_direction, ray_direction);
	b = 2 * inner_product(ray_direction, sphere_to_ray);
	c = inner_product(sphere_to_ray, sphere_to_ray) - ((object_diameter * object_diameter) / 4.0);
	discriminant = b * b - 4 * a * c;
	return discriminant;
}