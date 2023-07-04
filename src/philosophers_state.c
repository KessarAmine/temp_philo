/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_state.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmohamed <kmohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 16:52:39 by kmohamed          #+#    #+#             */
/*   Updated: 2023/07/03 12:08:51 by kmohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"
#include "../includes/memory.h"

int	take_chopstik(t_philosopher *philo)
{
	if (philo->id % 2 == 0)
		pthread_mutex_lock(philo->rightfork);
	else
		pthread_mutex_lock(philo->leftfork);
	if (!philosopher_is_dead(philo))
		put_msg(philo, "has taken a fork");
	if (philo->id % 2 == 0)
	{
		if (pthread_mutex_lock(philo->leftfork) != 0)
			return (pthread_mutex_unlock(philo->rightfork), 1);
		if (!philosopher_is_dead(philo))
			put_msg(philo, "has taken a fork");
	}
	else
	{
		if (pthread_mutex_lock(philo->rightfork) != 0)
			return (pthread_mutex_unlock(philo->leftfork), 1);
		if (!philosopher_is_dead(philo))
			put_msg(philo, "has taken a fork");
	}
	return (0);
}

void	eating(t_philosopher *philo)
{
	put_msg(philo, "is eating");
	pthread_mutex_lock(&philo->shared_memory->env_monitoring);
	philo->last_meal = get_time() - philo->shared_memory->time_starting;
	philo->time_to_die = philo->last_meal
		+ philo->shared_memory->time_to_die;
	if (philo->number_of_meals
		>= philo->shared_memory->number_of_meals)
		philo->shared_memory->philos_full++;
	pthread_mutex_unlock(&philo->shared_memory->env_monitoring);
	my_sleep(philo->shared_memory->time_to_eat, philo);
	pthread_mutex_lock(&philo->shared_memory->env_monitoring);
	if (philo->number_of_meals != -1)
		philo->number_of_meals++;
	pthread_mutex_unlock(&philo->shared_memory->env_monitoring);
	pthread_mutex_unlock(philo->rightfork);
	pthread_mutex_unlock(philo->leftfork);
}

void	sleeping(t_philosopher *philo)
{
	put_msg(philo, "is sleeping");
	my_sleep(philo->shared_memory->time_to_sleep, philo);
}

void	my_sleep(int time, t_philosopher *philo)
{
	int	start;

	start = get_time();
	while ((get_time() - start) < time
		&& philosopher_is_dead(philo) == 0)
		usleep(50);
}
