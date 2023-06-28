/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichinos <yichinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 16:23:31 by ynishimu          #+#    #+#             */
/*   Updated: 2023/06/28 15:43:17 by yichinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/calculate.h"

t_color	get_color(t_scene *scene, t_ray camera_ray);

static t_ray	get_camera_ray(int x, int y, t_camera *camera)
{
	t_ray	camera_ray;

	camera_ray.pos = camera->pos;
	camera_ray.dir.x = x - WIDTH / 2;
	camera_ray.dir.y = y - HEIGHT / 2;
	camera_ray.dir.z = -(WIDTH / (2.0 * tan(camera->fov / 2.0)));
	camera_ray.dir = norm_vec(camera_ray.dir);
	return (camera_ray);
}

void	render_scene(t_scene *scene)
{
	int			x;
	int			y;
	t_color		color;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			color = get_color(scene, get_camera_ray(x, y, &scene->camera));
			my_mlx_pixel_put(scene, x, y, color_to_int(color));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(scene->mlx.ptr, scene->mlx.window,
		scene->mlx.image.ptr, 0, 0);
}
