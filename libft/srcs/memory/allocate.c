/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_allocate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynishimu <ynishimu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 21:09:42 by ynishimu          #+#    #+#             */
/*   Updated: 2023/04/12 18:09:35 by ynishimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*alcd_ptr;

	if (size != 0 && count > SIZE_MAX / size)
		return (NULL);
	alcd_ptr = galloc(count * size);
	if (!alcd_ptr)
		return (NULL);
	ft_bzero(alcd_ptr, count * size);
	return (alcd_ptr);
}

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
	allocated = ft_calloc(1, size);
	if (!allocated)
	{
		gfree(garbages);
		return (NULL);
	}
	new = ft_lstnew(allocated);
	if (!new)
	{
		free(allocated);
		gfree(garbages);
		return (NULL);
	}
	ft_lstadd_back(&garbages, new);
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
