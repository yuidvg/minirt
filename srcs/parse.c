/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichinos <yichinos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 16:23:31 by ynishimu          #+#    #+#             */
/*   Updated: 2023/06/03 15:32:47 by yichinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

static void	set_ambient(char *line, t_ambient *ambient)
{
	char	**split;

	split = ft_split(line, ' ');
	if (!split || !split[0] || !split[1] || split[2]
		|| set_atod(split[1], &ambient->ratio)
		|| set_color(split[2], &ambient->color)
		|| !(0 <= ambient->ratio && ambient->ratio <= 1)
		|| !(0 <= ambient->color.r && ambient->color.r <= 255)
		|| !(0 <= ambient->color.g && ambient->color.g <= 255)
		|| !(0 <= ambient->color.b && ambient->color.b <= 255))
		gfree_exit(1, "Error\nFailed to parse ambient light");
}

static void	set_camera(char *line, t_camera *camera)
{
	char		**split;

	split = ft_split(line, ' ');
	if (!split || !split[0] || !split[1] || !split[2] || split[3]
		|| set_vector3(split[1], &camera->position)
		|| set_vector3(split[2], &camera->orientation)
		|| set_atoi(split[3], &camera->fov)
		|| !(0 <= camera->fov && camera->fov <= 180)
		|| !(0 <= camera->orientation.x && camera->orientation.x <= 1)
		|| !(0 <= camera->orientation.y && camera->orientation.y <= 1)
		|| !(0 <= camera->orientation.z && camera->orientation.z <= 1))
		gfree_exit(1, "Error\nFailed to parse camera");
}

static void	set_light(char *line, t_scene *scene)
{
	char		**split;

	split = ft_split(line, ' ');
	if (!split || !split[0] || !split[1] || !split[2] || split[3]
		|| set_vector3(split[1], &scene->light.position)
		|| set_atod(split[2], &scene->light.blightness)
		|| set_color(split[3], &scene->light.color)
		|| !(0 <= scene->light.blightness && scene->light.blightness <= 1)
		|| !(0 <= scene->light.color.r && scene->light.color.r <= 255)
		|| !(0 <= scene->light.color.g && scene->light.color.g <= 255)
		|| !(0 <= scene->light.color.b && scene->light.color.b <= 255))
		gfree_exit(1, "Error\nFailed to parse light");
}


void	init_scene(char *filename, t_scene *scene)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		gfree_exit(1, "Error\nFailed to open file");
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (ft_strncmp(line, "A ", 2))
			set_ambient(line + 2, scene);
		else if (ft_strncmp(line, "C ", 2))
			set_camera(line + 2, scene);
		else if (ft_strncmp(line, "L ", 2))
			set_light(line + 2, scene);
		else if (ft_strncmp(line, "sp ", 3)
			|| ft_strncmp(line, "pl ", 3) || ft_strncmp(line, "cy ", 3))
			add_object(line, scene);
		else
			gfree_exit(1, "Error\nFailed to parse scene");
	}
}
