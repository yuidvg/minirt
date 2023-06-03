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

static void	set_ambient(char *line, t_scene *scene)
{
	char	**split;

	split = ft_split(line, ' ');
	if (split[0] == NULL || split[1] == NULL)
		gfree_exit(1, "Error\nFailed to parse ambient light");
	scene->ambient = (t_ambient){
		.ratio = ft_atof(split[1]),
		.color = get_color(split[2])};
	free_split(split);
}

static void	set_camera(char *line, t_scene *scene)
{
	char	**split;
	t_camera	*camera;

	split = ft_split(line, ' ');
	if (split[0] == NULL || split[1] == NULL || split[2] == NULL || split[3] == NULL || split[4] == NULL || split[5] == NULL || split[6] == NULL || split[7] == NULL || split[8] == NULL)
		gfree_exit(1, "Error\nFailed to parse camera");
	camera = (t_camera *)malloc(sizeof(t_camera));
	if (camera == NULL)
		gfree_exit(1, "Error\nFailed to allocate memory");
	camera->position = (t_vector3){ft_atof(split[1]), ft_atof(split[2]), ft_atof(split[3])};
	camera->orientation = (t_vector3){ft_atof(split[4]), ft_atof(split[5]), ft_atof(split[6])};
	camera->fov = ft_atof(split[7]);
	camera->viewport_width = ft_atof(split[8]);
	camera->viewport_height = camera->viewport_width / scene->aspect_ratio;
	camera->viewport_distance = camera->viewport_width / (2 * tan(camera->fov / 2));
	camera->viewport_origin = (t_vector3){
		camera->position.x + camera->orientation.x * camera->viewport_distance,
		camera->position.y + camera->orientation.y * camera->viewport_distance,
		camera->position.z + camera->orientation.z * camera->viewport_distance};
	camera->viewport_horizontal = cross_product(camera->orientation, (t_vector3){0, 1, 0});
	camera->viewport_vertical = cross_product(camera->viewport_horizontal, camera->orientation);
	camera->viewport_horizontal = normalize(camera->viewport_horizontal);
	camera->viewport_vertical = normalize(camera->viewport_vertical);
	camera->viewport_horizontal = scale_vector(camera->viewport_horizontal, camera->viewport_width);
	camera->viewport_vertical = scale_vector(camera->viewport_vertical, camera->viewport_height);
	camera->viewport_top_left = (t_vector3){
		camera->viewport_origin.x - camera->viewport_horizontal.x / 2 + camera->viewport_vertical.x / 2,
		camera->viewport_origin.y - camera->viewport_horizontal.y / 2 + camera->viewport_vertical.y / 2,
		camera->viewport_origin.z - camera->viewport_horizontal.z / 2 + camera->viewport_vertical.z
		/ 2};
	camera->next = scene->camera;
	scene->camera = camera;
	free_split(split);
}

static void	set_light(char *line, t_scene *scene)
{
	char	**split;
	t_light	*light;

	split = ft_split(line, ' ');
	if (split[0] == NULL || split[1] == NULL || split[2] == NULL || split[3] == NULL)
		gfree_exit(1, "Error\nFailed to parse light");
	light = (t_light *)malloc(sizeof(t_light));
	if (light == NULL)
		gfree_exit(1, "Error\nFailed to allocate memory");
	light->position = (t_vector3){ft_atof(split[1]), ft_atof(split[2]), ft_atof(split[3])};
	light->ratio = ft_atof(split[4]);
	light->color = get_color(split[5]);
	light->next = scene->light;
	scene->light = light;
	free_split(split);
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
			set_ambient(line, scene);
		else if (ft_strncmp(line, "C ", 2))
			set_camera(line, scene);
		else if (ft_strncmp(line, "L ", 2))
			set_light(line, scene);
		else if (ft_strncmp(line, "sp ", 3))
			add_sphere(line, scene);
		else if (ft_strncmp(line, "pl ", 3))
			add_plane(line, scene);
		else if (ft_strncmp(line, "cy ", 3))
			add_cylinder(line, scene);
		free(line);
	}
}
