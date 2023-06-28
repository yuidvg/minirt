/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichinos <yichinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 16:23:31 by ynishimu          #+#    #+#             */
/*   Updated: 2023/06/28 18:07:32 by yichinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "libs.h"
# include "calculate.h"
# include "types.h"
# include "macos_keys.h"

void	init_mlx(t_scene *scene);
void	init_scene(char *filename, t_scene *scene);
void	my_mlx_pixel_put(t_scene *scene, int x, int y, int color);
void	render_scene(t_scene *scene);

#endif
