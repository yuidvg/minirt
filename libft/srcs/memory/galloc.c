/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynishimu <ynishimu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 18:00:05 by ynishimu          #+#    #+#             */
/*   Updated: 2023/04/15 18:07:43 by ynishimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libs.h"
#include "../../includes/types.h"

static void	gfree(t_list *garbages)
{
	t_list	*tmp;

	while (garbages)
	{
		tmp = garbages->next;
		free(garbages->content);
		free(garbages);
		garbages = tmp;
	}
}

void	*galloc(size_t size)
{
	void			*allocated;
	t_list			*new;
	static t_list	*garbages;

	if (size == 0)
	{
		gfree(garbages);
		return (NULL);
	}
	allocated = malloc(size);
	if (!allocated)
	{
		gfree(garbages);
		return (NULL);
	}
	new = lstnew(allocated);
	if (!new)
	{
		free(allocated);
		gfree(garbages);
		return (NULL);
	}
	lstadd_back(&garbages, new);
	return (allocated);
}

void	gfree_exit(int exit_status, char *fmt, ...)
{
	va_list	ap;

	if (fmt)
	{
		va_start(ap, fmt);
		ft_vdprintf(STDERR_FILENO, fmt, ap);
		va_end(ap);
	}	
	galloc(0);
	exit(exit_status);
}
