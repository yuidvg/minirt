/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichinos <$yichinos@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 16:23:31 by ynishimu          #+#    #+#             */
/*   Updated: 2023/06/27 10:28:27 by yichinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# define WIDTH 800
# define HEIGHT 600

# define WINDOW_TITLE "miniRT"
# define DIFFUSE_RATIO 0.8
# define SPECULAR_RATIO 0.2

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

typedef struct s_ray
{
	t_vector3	pos;
	t_vector3	dir;
}	t_ray;

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
	t_vector3	pos;
	t_vector3	dir;
	int			fov;
}	t_camera;

typedef struct s_light
{
	t_vector3	pos;
	double		blightness;
	t_color		color;
}	t_light;

struct	s_object;

typedef struct s_
{
	struct s_object	*this;
	t_ray			*camera_ray;
}	t_;

typedef struct s_object
{
	t_color				color;
	t_vector3			pos;
	t_vector3			dir;
	double				rad;
	double				height;
	t_ray				(*get_inter_point)(t_ *);
	struct s_object		*next;
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
