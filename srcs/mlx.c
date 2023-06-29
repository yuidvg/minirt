/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichinos <yichinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 16:23:31 by ynishimu          #+#    #+#             */
/*   Updated: 2023/06/28 18:13:29 by yichinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

static int	mlx_exit(t_mlx *mlx)
{
	mlx_destroy_image(mlx->ptr, mlx->image.ptr);
	mlx_destroy_window(mlx->ptr, mlx->window);
	gfree_exit(0, NULL);
	exit(0);
}

static int	key_hook(int key, t_scene *scene)
{
	if (key == KEY_ESC)
		mlx_exit(&scene->mlx);
	return (0);
}

void	init_mlx(t_scene *scene)
{
	scene->mlx.ptr = mlx_init();
	if (!scene->mlx.ptr)
		exit(-1);
	scene->mlx.window
		= mlx_new_window(scene->mlx.ptr, WIDTH, HEIGHT, WINDOW_TITLE);
	if (!scene->mlx.window)
		ft_exit(-1, scene->mlx.ptr, NULL, NULL);
	scene->mlx.image.ptr = mlx_new_image(scene->mlx.ptr, WIDTH, HEIGHT);
	if (!scene->mlx.image.ptr)
		ft_exit(-1, scene->mlx.ptr, scene->mlx.window, NULL);
	scene->mlx.image.addr
		= mlx_get_data_addr(scene->mlx.image.ptr, &scene->mlx.image.bpp,
			&scene->mlx.image.line_len, &scene->mlx.image.endian);
	if (!scene->mlx.image.addr)
		ft_exit(-1, scene->mlx.ptr, scene->mlx.window, scene->mlx.image.ptr);
	mlx_hook(scene->mlx.window, 17, 1L << 17, mlx_exit, scene);
	mlx_hook(scene->mlx.window, 2, 0, key_hook, scene);
}

void	my_mlx_pixel_put(t_scene *scene, int x, int y, int color)
{
	char	*dst;

	dst = scene->mlx.image.addr + (y * scene->mlx.image.line_len + x
			* (scene->mlx.image.bpp / 8));
	*(unsigned int *)dst = color;
}
