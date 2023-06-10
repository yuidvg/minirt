/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichinos <yichinos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 16:23:31 by ynishimu          #+#    #+#             */
/*   Updated: 2023/06/10 16:58:35 by yichinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CALCULATE_H
# define CALCULATE_H

# include "libs.h"
# include "types.h"

// Vector
t_vector3	scale_vector(t_vector3 v, double scalar);
double		magnitude_vector(t_vector3 vector);
t_vector3	normalize_vector(t_vector3 v);


//Vectors
t_vector3	add_vectors(t_vector3 v1, t_vector3 v2);
t_vector3	subtract_vectors(t_vector3 v1, t_vector3 v2);
double		inner_product_vectors(t_vector3 v1, t_vector3 v2);

// Scalar
double		clamp(double value, double min, double max);
// int			set_atod(char *str, double *num);

// Calculation
t_vector3	calculate_ray_direction(int x, int y);
double		calculate_discriminant(t_vector3 ray_direction,
				t_vector3 ray_origin, t_vector3 object_position,
				double object_diameter);

// Color
void		set_objects_color(t_scene *scene, int x, int y, double diffuse);

// Sphere
t_color		extract_color_components(t_color source_color);
t_color		calculate_shade_color(t_scene *scene, double diffuse);
double		process_intersection(t_scene *scene,
				t_vector3 ray_direction, double t);
void		set_sphere_color(t_scene *scene, int x, int y, double diffuse);
void		render_sphere(t_scene *scene, int x, int y);

#endif
