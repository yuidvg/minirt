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
	if (!split || split[0] == NULL || split[1] == NULL
		|| set_atod(split[1], &ambient->ratio)
		|| set_color(split[2], &ambient->color))
		gfree_exit(1, "Error\nFailed to parse ambient light");
}

static void	set_camera(char *line, t_camera *camera)
{
	char		**split;

	split = ft_split(line, ' ');
	if (!split || !split[1] || !split[2] || split[3]
		|| set_vector3(split[1], &camera->position)
		|| set_vector3(split[2], &camera->direction)
		|| set_atoi(split[3], &camera->fov))
		gfree_exit(1, "Error\nFailed to parse camera");
}

static void	set_light(char *line, t_scene *scene)
{
	char	**split;
	t_light	*light;

	split = ft_split(line, ' ');
	if (split[0] == NULL || split[1] == NULL || split[2] == NULL || split[3] == NULL)
		gfree_exit(1, "Error\nFailed to parse light");
	light = (t_light *)galloc(sizeof(t_light));
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
