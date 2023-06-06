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

#ifndef UTILS_H
# define UTILS_H

# include "libs.h"
# include "types.h"

//Vector
t_vector3	add_vectors(t_vector3 v1, t_vector3 v2);
t_vector3	scale_vector(t_vector3 v, double scalar);
double		inner_product(t_vector3 v1, t_vector3 v2);
t_vector3	subtract_vectors(t_vector3 v1, t_vector3 v2);
t_vector3	normalize(t_vector3 v);

//Scalar
double		clamp(double value, double min, double max);
int			set_atod(char *str, double *num);

//Calculation
t_vector3	calculate_ray_direction(int x, int y);
double		calculate_discriminant(t_vector3 ray_direction, t_vector3 ray_origin,
								t_vector3 object_position, double object_diameter);

//Color
int	set_color(char *str, t_color *color)

#endif
