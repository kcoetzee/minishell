/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcoetzee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 14:04:03 by kcoetzee          #+#    #+#             */
/*   Updated: 2017/09/25 14:05:52 by kcoetzee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"


void	print_heap()
{
	t_heap *itt;
	int i;
	itt = heap.next;

	i = 0;
	while (itt)
	{
		fprintf(stderr, "BLOCK [%i]: %p$\n", i++, itt->address);   
		itt = itt->next;	
	}
}

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

void	free_heap()
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
	//fprintf(stderr, "Trying to free memory that was not allocated through E_MALLOC\n");
}

void	init_heap()
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
	{
		//fprintf(stderr, "ATTEMPTING TO FREE NULL MEMORY\n");
		return ;
	}

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
	//fprintf(stderr, "Trying to free memory that was not allocated through E_MALLOC\n");
	return ;
}

void	*e_malloc(int size)
{
	void *result;

	//printf("%s\n", "MALLOC");
	result = malloc(size);
	heap_push(result);
	return (result);
}

