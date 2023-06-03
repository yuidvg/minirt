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

#ifndef TYPES_H
# define TYPES_H

# define WIDTH 800
# define HEIGHT 600

typedef struct s_vector3
{
	double	x;
	double	y;
	double	z;
}	t_vector3;

typedef struct s_sphere
{
	t_vector3	position;
	double		radius;
	int			color;
}	t_sphere;

typedef struct s_plane
{
	t_vector3	position;
	t_vector3	normal;
	int			color;
}	t_plane;

typedef struct s_scene
{
	t_sphere	sphere;
	t_vector3	light;
	t_plane		plane;
}	t_scene;

#endif