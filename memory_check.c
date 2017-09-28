/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcoetzee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 14:04:03 by kcoetzee          #+#    #+#             */
/*   Updated: 2017/09/28 11:11:30 by kcoetzee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/*
**void	print_heap(void)
**{
**	t_heap	*itt;
**	int		i;
**
**	itt = heap.next;
**	i = 0;
**	while (itt)
**	{
**		fprintf(stderr, "BLOCK [%i]: %p$\n", i++, itt->address);
**		itt = itt->next;
**	}
**}
*/

void	heap_push(void *address)
{
	t_heap *new;
	t_heap *itt;

	itt = &heap;
	new = (t_heap*)malloc(sizeof(t_heap));
	new->address = address;
	while (itt->next != NULL)
		itt = itt->next;
	itt->next = new;
	itt->next->next = NULL;
}

void	free_heap(void)
{
	t_heap *itt;
	t_heap *prev;

	prev = &heap;
	itt = heap.next;
	while (itt)
	{
		heap.next = itt->next;
		free(itt->address);
		itt->address = NULL;
		free(itt);
		itt = heap.next;
	}
	heap.next = NULL;
}

void	init_heap(void)
{
	heap.address = NULL;
	heap.next = NULL;
}

void	e_free(void *memory)
{
	t_heap *itt;
	t_heap *prev;

	prev = &heap;
	itt = heap.next;
	if (memory == NULL)
		return ;
	while (itt)
	{
		if (itt->address == memory)
		{
			prev->next = itt->next;
			free(itt->address);
			itt->address = NULL;
			free(itt);
			return ;
		}
		prev = itt;
		itt = prev->next;
	}
	return ;
}

void	*e_malloc(int size)
{
	void *result;

	result = malloc(size);
	heap_push(result);
	return (result);
}
