/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmohamed <kmohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 13:20:04 by kmohamed          #+#    #+#             */
/*   Updated: 2023/06/05 13:27:22 by kmohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/memory.h"

void	add_mem_block(void **p_head, void *ptr, size_t size)
{
	t_memory_block	*block;

	block = (t_memory_block *) malloc(sizeof(t_memory_block));
	block->adresse = ptr;
	block->size = size;
	block->next = *p_head;
	*p_head = block;
}

void	remove_mem_block(void **p_head, void *ptr)
{
	t_memory_block	*block;
	t_memory_block	*prev;

	block = *p_head;
	prev = NULL;
	while (block != NULL)
	{
		if (block->adresse == ptr)
		{
			if (prev == NULL)
				*p_head = block->next;
			else
				prev->next = block->next;
			free(block);
			break ;
		}
		prev = block;
		block = block->next;
	}
}

void	*my_malloc(void **p_head, size_t size)
{
	void	*adresse;

	adresse = malloc(size);
	add_mem_block(p_head, adresse, size);
	return (adresse);
}

void	my_free(void **p_head, void *adresse)
{
	remove_mem_block(p_head, adresse);
	free(adresse);
}

void	free_all_mem(void **p_head)
{
	t_memory_block	*node;
	t_memory_block	*next;

	next = NULL;
	node = *p_head;
	while (node != NULL)
	{
		next = node->next;
		free(node->adresse);
		free(node);
		node = next;
	}
	*p_head = NULL;
}
