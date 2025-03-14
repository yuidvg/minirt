/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichinos <yichinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 16:23:31 by ynishimu          #+#    #+#             */
/*   Updated: 2023/07/09 12:04:38 by yichinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "libs.h"
# include "types.h"

int		parse_color(char *str, t_color *color);
int		filename_check(char *filename);
int		set_atod(char *str, double *num);
int		set_atoi(char *str, int *num);
int		parse_vector3(char *str, t_vector3 *vec);
int		parse_normalized_vector3(char *str, t_vector3 *vector);
void	add_object(char *str, t_object **object);

#endif
