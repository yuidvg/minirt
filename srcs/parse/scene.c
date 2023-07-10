/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichinos <yichinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 16:23:31 by ynishimu          #+#    #+#             */
/*   Updated: 2023/07/09 12:05:58 by yichinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parse.h"

static void	parse_ambient(char *line, t_ambient *ambient)
{
	char		**split;
	static int	parsed;

	if (parsed)
		gfree_exit(1, "Error\nMore than 1 Ambient light.\n");
	split = ft_split(line, ' ');
	if (!split || !split[0] || !split[1] || split[2]
		|| set_atod(split[0], &ambient->ratio)
		|| !(0 <= ambient->ratio && ambient->ratio <= 1)
		|| parse_color(split[1], &ambient->color))
		gfree_exit(1, "Error\nFailed to parse ambient light\n");
	parsed = 1;
}

static void	parse_camera(char *line, t_camera *camera)
{
	char		**split;
	static int	parsed;

	if (parsed)
		gfree_exit(1, "Error\nMore than 1 Camera.\n");
	split = ft_split(line, ' ');
	if (!split || !split[0] || !split[1] || !split[2] || split[3]
		|| parse_vector3(split[0], &camera->pos)
		|| parse_normalized_vector3(split[1], &camera->dir)
		|| set_atoi(split[2], &camera->fov)
		|| !(0 <= camera->fov && camera->fov <= 180))
		gfree_exit(1, "Error\nFailed to parse camera\n");
	parsed = 1;
}

static void	parse_light(char *line, t_light *light)
{
	char		**split;
	static int	parsed;

	if (parsed)
		gfree_exit(1, "Error\nMore than 1 Light.\n");
	split = ft_split(line, ' ');
	if (!split || !split[0] || !split[1] || !split[2] || split[3]
		|| parse_vector3(split[0], &light->pos)
		|| set_atod(split[1], &light->blightness)
		|| !(0 <= light->blightness && light->blightness <= 1)
		|| parse_color(split[2], &light->color))
		gfree_exit(1, "Error\nFailed to parse light\n");
	parsed = 1;
}

static void	parse_line(char *line, t_scene *scene, int parsed_acl[3])
{
	if (!ft_strncmp(line, "A ", 2))
	{
		parse_ambient(line + 2, &scene->ambient);
		parsed_acl[0]++;
	}
	else if (!ft_strncmp(line, "C ", 2))
	{
		parse_camera(line + 2, &scene->camera);
		parsed_acl[1]++;
	}
	else if (!ft_strncmp(line, "L ", 2))
	{
		parse_light(line + 2, &scene->light);
		parsed_acl[2]++;
	}
	else if (!ft_strncmp(line, "sp ", 3)
		|| !ft_strncmp(line, "pl ", 3) || !ft_strncmp(line, "cy ", 3))
		add_object(line, &scene->objects);
	else
		gfree_exit(1, "Error\nFailed to parse scene.\n");
}

void	init_scene(char *filename, t_scene *scene)
{
	int		fd;
	char	*line;
	int		parsed_acl[3];

	if (filename_check(filename))
		gfree_exit(1, "Error\nFailed to open file\n");
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		gfree_exit(1, "Error\nFailed to open file\n");
	scene->objects = NULL;
	parsed_acl[0] = 0;
	parsed_acl[1] = 0;
	parsed_acl[2] = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (*line != '\n')
			parse_line(line, scene, parsed_acl);
	}
	if (parsed_acl[0] != 1 || parsed_acl[1] != 1 || parsed_acl[2] != 1)
		gfree_exit(1, "Error\nFailed to parse scene.\n");
}
