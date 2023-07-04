/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmohamed <kmohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 22:00:32 by kmohamed          #+#    #+#             */
/*   Updated: 2023/07/03 14:49:44 by kmohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"
#include "../includes/memory.h"

int	philo_starving(t_philosopher *philo)
{
	if (get_time() - philo->shared_memory->time_starting
		> philo->time_to_die)
	{
		philo->shared_memory->philosopher_dead = 1;
		printf("%d %d died\n",
			get_time() - philo->shared_memory->time_starting,
			philo->id);
		return (0);
	}
	else
		return (1);
}

int	is_dead(t_philosophers_env *env)
{
	int	i;

	i = 0;
	while (i < env->size)
	{
		if (philo_starving(&env->philosophers[i]) == 0)
			return (STARVING_ERROR);
		i++;
	}
	return (1);
}

void	free_philosophers(t_philosophers_env *env)
{
	free(env->philosophers);
	free(env->chop_sticks);
}

void	*scheduler_routine(void *data)
{
	t_philosophers_env	*env;

	env = (t_philosophers_env *) data;
	while (1)
	{
		if (check_foodlimit(env))
			return (NULL);
		pthread_mutex_lock(&env->env_monitoring);
		if (is_dead(env) == STARVING_ERROR)
		{
			usleep(100);
			pthread_mutex_unlock(&env->env_monitoring);
			return (NULL);
		}
		pthread_mutex_unlock(&env->env_monitoring);
		usleep(200);
	}
}

int	get_time(void)
{
	static struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}
