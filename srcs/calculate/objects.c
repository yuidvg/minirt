/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynishimu <ynishimu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 16:23:31 by ynishimu          #+#    #+#             */
/*   Updated: 2023/04/11 16:08:45 by ynishimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/calculate.h"

t_object	*new_object(t_object object)
{
	t_object	*new;

	new = galloc(sizeof(t_object));
	new->type = object.type;
	new->color = object.color;
	new->position = object.position;
	new->axis = object.axis;
	new->diameter = object.diameter;
	new->height = object.height;
	new->next = NULL;
	return (new);
}
