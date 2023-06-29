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
void	my_mlx_pixel_put(t_scene *scene, int x, int y, int color);

static void	set_orthonormal_basis(t_vector3 *esx, t_vector3 *esy,
t_vector3 d)
{
	esx->z = -d.x
		/ sqrt(d.x * d.x + d.z * d.z);
	esx->y = 0;
	esx->x = d.z
		/ sqrt(d.x * d.x + d.z * d.z);
	*esy = cross_vecs(d, *esx);
}

static t_ray	get_camera_ray(int x, int y, t_camera *camera)
{
	t_vector3	esx;
	t_vector3	esy;
	t_vector3	ps;
	t_vector3	dsc;
	t_vector3	camera_ray_dir;

	set_orthonormal_basis(&esx, &esy, camera->dir);
	ps = add_vecs(scl_vec(esx, (x - WIDTH / 2)),
			scl_vec(esy, (y - HEIGHT / 2)));
	dsc = scl_vec(camera->dir, WIDTH / 2 / tan(camera->fov / 2));
	camera_ray_dir
		= scl_vec(add_vecs(dsc, ps),
			1 / magn_vec(add_vecs(dsc, ps)));
	return ((t_ray){.pos = camera->pos, .dir = camera_ray_dir});
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
