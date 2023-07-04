/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_threads.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmohamed <kmohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 21:12:21 by kmohamed          #+#    #+#             */
/*   Updated: 2023/07/04 11:56:57 by kmohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"
#include "../includes/memory.h"

void	*philosophers_routine(void *data)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)data;
	if ((philo->id % 2))
		time_wait(5);
	while (philo->shared_memory->philosopher_dead == 0)
	{
		if (check_foodlimit(philo->shared_memory))
			return (NULL);
		if (philosopher_is_dead(philo))
			return (0);
		take_chopstik(philo);
		if (philosopher_is_dead(philo))
		{
			pthread_mutex_unlock(philo->leftfork);
			pthread_mutex_unlock(philo->rightfork);
			return (0);
		}
		eating(philo);
		if (philosopher_is_dead(philo))
			return (0);
		sleeping(philo);
		if (philosopher_is_dead(philo))
			return (0);
		philosophers_is_thinking(philo);
	}
	return (0);
}

void	threads_join(t_philosophers_env *env)
{
	int	i;

	i = -1;
	while (++i < env->size)
		pthread_join(env->philosophers[i].thread_id, NULL);
}

void	threads_start(t_philosophers_env *env)
{
	int				i;

	i = 0;
	env->time_starting = get_time();
	while (i < env->size)
	{
		if (pthread_create(&env->philosophers[i].thread_id,
				NULL, &philosophers_routine,
				(void *)&env->philosophers[i]) != 0)
			throw_error(THREAD_ERROR, env);
		i++;
	}
	i = 0;
}

int	philosopher_is_dead(t_philosopher *philosophers)
{
	pthread_mutex_lock(&philosophers->shared_memory->env_monitoring);
	if (philosophers->shared_memory->philosopher_dead == 1)
	{
		pthread_mutex_unlock(&philosophers->shared_memory->env_monitoring);
		return (1);
	}
	pthread_mutex_unlock(&philosophers->shared_memory->env_monitoring);
	return (0);
}

int	check_foodlimit(t_philosophers_env *env)
{
	pthread_mutex_lock(&env->env_monitoring);
	if (env->philos_full
		>= env->number_of_meals
		&& env->number_of_meals != -1)
	{
		pthread_mutex_unlock(&env->env_monitoring);
		return (1);
	}
	pthread_mutex_unlock(&env->env_monitoring);
	return (0);
}

void	time_wait(int time)
{
	useconds_t	microsecond;

	microsecond = (useconds_t) time * 1000;
	usleep(microsecond);
}
