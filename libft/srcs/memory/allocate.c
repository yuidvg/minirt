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
	alcd_ptr = malloc(count * size);
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

static t_list	*lstnew(t_list *content)
{
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		gfree_exit(-1, "Error: malloc failed\n");
	new_node->content = content;
	return (new_node);
}

void	*galloc(size_t size)
{
	void			*new_mem;
	t_list			*new_node;
	static t_list	*garbages;

	if (size == 0)
	{
		gfree(garbages);
		return (NULL);
	}
	new_mem = malloc(size);
	if (!new_mem)
		gfree_exit(-1, "FATAL: malloc failed\n");
	new_node = lstnew(new_mem);
	ft_lstadd_front(&garbages, new_node);
	return (new_mem);
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
