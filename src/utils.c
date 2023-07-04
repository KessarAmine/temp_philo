/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmohamed <kmohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 18:56:30 by kmohamed          #+#    #+#             */
/*   Updated: 2023/07/03 15:21:46 by kmohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	is_sign(char s)
{
	if (s == '+')
		return (1);
	return (0);
}

static int	is_digit(char c)
{
	if (c <= '9' && c >= '0')
		return (1);
	return (0);
}

int	is_number(char *av)
{
	int	i;

	i = 0;
	if (is_sign(av[i]) && av[i + 1] != '\0')
		i++;
	while (av[i] && is_digit(av[i]))
		i++;
	if (av[i] != '\0' && !is_digit(av[i]))
		return (0);
	return (1);
}

long int	ft_atoi(const char *str)
{
	long int	nb;
	int			isneg;
	int			i;

	nb = 0;
	isneg = 1;
	i = 0;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		isneg *= -1;
		i++;
	}
	while (is_digit(str[i]))
	{
		nb = (nb * 10) + (str[i] - '0');
		i++;
	}
	return (nb * isneg);
}

void	put_msg(t_philosopher *philo, char *str)
{
	pthread_mutex_lock(&philo->shared_memory->env_monitoring);
	if (philo->shared_memory->philosopher_dead != 1)
	{
		printf("%d %d %s\n", get_time()
			- philo->shared_memory->time_starting, philo->id, str);
	}
	pthread_mutex_unlock(&philo->shared_memory->env_monitoring);
}
