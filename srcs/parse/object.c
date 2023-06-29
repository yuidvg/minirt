/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichinos <yichinos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 16:23:31 by ynishimu          #+#    #+#             */
/*   Updated: 2023/06/13 18:57:26 by yichinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parse.h"
#include "../includes/calculate.h"

static int	parse_sphere(char *line, t_object *object)
{
	char		**split;

	split = ft_split(line, ' ');
	if (!split
		|| !split[0] || !split[1] || !split[2] || split[3]
		|| parse_vector3(split[0], &object->pos)
		|| set_atod(split[1], &object->rad)
		|| parse_color(split[2], &object->color)
		|| !(0 <= object->rad))
		return (1);
	object->rad /= 2;
	object->get_intersection = get_intersection_sphere;
	return (0);
}

static int	parse_plane(char *line, t_object *object)
{
	char		**split;

	split = ft_split(line, ' ');
	if (!split
		|| !split[0] || !split[1] || !split[2] || split[3]
		|| parse_vector3(split[0], &object->pos)
		|| parse_vector3(split[1], &object->dir)
		|| object->dir.x < 0 || object->dir.y < 0 || object->dir.z < 0
		|| object->dir.x > 1 || object->dir.y > 1 || object->dir.z > 1
		|| parse_color(split[2], &object->color))
		return (1);
	object->dir = norm_vec(object->dir);
	object->get_intersection = get_intersection_plane;
	return (0);
}

static int	parse_cylinder(char *line, t_object *object)
{
	char		**split;

	split = ft_split(line, ' ');
	if (!split
		|| !split[0] || !split[1] || !split[2] || !split[3] || !split[4]
		|| split[5]
		|| parse_vector3(split[0], &object->pos)
		|| parse_vector3(split[1], &object->dir)
		|| object->dir.x < 0 || object->dir.y < 0 || object->dir.z < 0
		|| object->dir.x > 1 || object->dir.y > 1 || object->dir.z > 1
		|| set_atod(split[2], &object->rad)
		|| set_atod(split[3], &object->height)
		|| parse_color(split[4], &object->color)
		|| !(0 <= object->rad)
		|| !(0 <= object->height))
		return (1);
	object->rad /= 2;
	object->dir = norm_vec(object->dir);
	object->get_intersection = get_intersection_cylinder;
	return (0);
}

int	add_object(char *str, t_object **object)
{
	t_object	*new;

	new = (t_object *)galloc(sizeof(t_object));
	if (ft_strncmp(str, "sp ", 3) == 0)
	{
		if (parse_sphere(str + 3, new))
			return (1);
	}
	else if (ft_strncmp(str, "pl ", 3) == 0)
	{
		if (parse_plane(str + 3, new))
			return (1);
	}
	else if (ft_strncmp(str, "cy ", 3) == 0)
	{
		if (parse_cylinder(str + 3, new))
			return (1);
	}
	new->next = *object;
	*object = new;
	return (0);
}
