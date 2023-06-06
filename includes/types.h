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

# define WINDOW_TITLE "miniRT"

typedef enum e_object_type
{
	SPHERE,
	PLANE,
	CYLINDER,
}	t_object_type;

typedef struct s_vector3
{
	double	x;
	double	y;
	double	z;
}	t_vector3;

typedef struct s_color
{
	int		r;
	int		g;
	int		b;
}	t_color;

typedef struct s_image
{
	void	*ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_image;

typedef struct s_mlx
{
	void		*ptr;
	void		*window;
	t_image		image;
}	t_mlx;

typedef struct s_ambient
{
	double	ratio;
	t_color	color;
}	t_ambient;

typedef struct s_camera
{
	t_vector3	position;
	t_vector3	orientation;
	int			fov;
}	t_camera;

typedef struct s_light
{
	t_vector3	position;
	double		blightness;
	t_color		color;
}	t_light;

typedef struct s_object
{
	t_object_type	type;
	t_color			color;
	t_vector3		position;
	t_vector3		axis;
	double			diameter;
	double			height;

	struct s_object	*next;
}	t_object;

typedef struct s_scene
{
	t_mlx		mlx;
	t_ambient	ambient;
	t_camera	camera;
	t_light		light;

	t_object	*objects;
}	t_scene;

#endif
