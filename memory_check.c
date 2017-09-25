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
	itt = &heap;

	i = 0;
	while (itt)
	{
		fprintf(stderr, "BLOCK [%i]: %p$\n", i++, itt->address);   
		itt = itt->next;	
	}
}

void	heap_push(void *address)
{
	// Allocate memory for the node
	t_heap *itt;
	itt = &heap;
	if (heap.next == NULL && heap.address == NULL)
	{
		//itt->next = malloc(sizeof(t_heap));
		//itt = itt->next;
		//itt->address = address;
		heap.address = address;
		return ;
	}
		
	while (itt->next != NULL){
		itt = itt->next;
	}

	itt->next = malloc(sizeof(t_heap));
	itt->next->address = address;
	itt->next->next = NULL;
}

void	free_heap()
{
	t_heap *itt;
	int i;
	itt = &heap;

	i = 0;
	while (itt)
	{
		free(itt->address);
		itt->address = NULL;
		itt = itt->next;	
	}
}

void	init_heap()
{
	heap.address = NULL;
	heap.next = NULL;
}

void	*e_malloc(int size)
{
	void *result;

	result = malloc(size);
	heap_push(result);
	return (result);
}

