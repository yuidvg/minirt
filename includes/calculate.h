/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichinos <yichinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 16:23:31 by ynishimu          #+#    #+#             */
/*   Updated: 2023/06/28 11:33:33 by yichinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CALCULATE_H
# define CALCULATE_H

# include "libs.h"
# include "types.h"

//Object
t_ray		get_intersection_plane(t_ *data);
t_ray		get_intersection_sphere(t_ *data);
t_ray		get_intersection_cylinder(t_ *data);

// Vector
t_vector3	scl_vec(t_vector3 v, double scalar);
double		magn_vec(t_vector3 vector);
t_vector3	norm_vec(t_vector3 v);

//Vectors
t_vector3	add_vecs(t_vector3 v1, t_vector3 v2);
t_vector3	sub_vecs(t_vector3 v1, t_vector3 v2);
double		dot_vecs(t_vector3 v1, t_vector3 v2);

// double
double		clamp(double value, double min, double max);
double		min(double a, double b);
// int			set_atod(char *str, double *num);

// Calculation
t_vector3	calculate_ray_direction(int x, int y);
double		calculate_discriminant(t_vector3 ray_direction,
				t_vector3 ray_origin, t_vector3 object_position,
				double object_diameter);

// Color
void		set_objects_color(t_scene *scene, int x, int y, double diffuse);
t_color		add_colors(t_color color1, t_color color2);
t_color		scale_color(t_color color, double scale);

// Sphere
t_color		extract_color_components(t_color source_color);
t_color		calculate_shade_color(t_scene *scene,
				double diffuse, t_color color);
double		process_intersection(t_scene *scene,
				t_vector3 ray_direction, double t);
void		set_sphere_color(t_scene *scene, int x, int y, double diffuse);
void		render_sphere(t_scene *scene, int x, int y);

#endif
