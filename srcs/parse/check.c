/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichinos <yichinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 11:50:50 by yichinos          #+#    #+#             */
/*   Updated: 2023/07/09 12:04:30 by yichinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

int	filename_check(char *filename)
{
	char	*file_last_name;

	file_last_name = ft_strrchr(filename, '/');
	if (file_last_name)
		file_last_name++;
	else
		file_last_name = filename;
	if (ft_strlen(file_last_name) <= ft_strlen(".rt") || \
		ft_strncmp(file_last_name + ft_strlen(file_last_name) \
		- ft_strlen(".rt"), ".rt", 4))
		return (1);
	return (0);
}
