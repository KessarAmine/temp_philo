/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_points.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmohamed <kmohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 18:31:01 by kmohamed          #+#    #+#             */
/*   Updated: 2023/07/03 15:23:39 by kmohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"
#include "../includes/memory.h"

int	throw_error(t_erros error, t_philosophers_env *env)
{
	if (error == ARG_ERROR)
		printf("[ARG_ERROR...]\n");
	if (error == HEAP_ERROR)
		printf("HEAP_ERROR\n");
	if (error == THREAD_ERROR)
		printf("THREAD_ERROR\n");
	free_philosophers(env);
	return (1);
}

void	philosophers_is_thinking(t_philosopher *philo)
{
	put_msg(philo, "is thinking");
}
