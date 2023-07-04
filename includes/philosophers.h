/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmohamed <kmohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 18:14:26 by kmohamed          #+#    #+#             */
/*   Updated: 2023/07/04 11:57:12 by kmohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philosopher
{
	int							id;
	pthread_t					thread_id;
	pthread_mutex_t				*leftfork;
	pthread_mutex_t				*rightfork;
	int							last_meal;
	int							is_eating;
	int							time_to_die;
	int							time_to_sleep;
	int							time_to_eat;
	int							number_of_meals;
	struct s_philosophers_env	*shared_memory;
}				t_philosopher;

typedef struct s_philosophers_env
{
	void			*memory_blocks;
	t_philosopher	*philosophers;
	pthread_mutex_t	*chop_sticks;
	pthread_mutex_t	env_monitoring;
	int				size;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_meals;
	int				philosopher_dead;
	int				time_starting;
	int				philos_full;
}				t_philosophers_env;

typedef enum s_erros
{
	ARG_ERROR,
	THREAD_ERROR,
	HEAP_ERROR,
	STARVING_ERROR
}				t_erros;

long int	ft_atoi(const char *str);
int			is_number(char *av);
int			exit_simulation( t_philosophers_env *env);
int			throw_error(t_erros error, t_philosophers_env *env);
void		put_msg(t_philosopher *philo, char *str);
int			get_time(void);
void		time_wait(int time);

int			env_init(t_philosophers_env *env, char **argv);
int			input_read(char **argv, t_philosophers_env *env);
void		philosophers_is_thinking(t_philosopher *philo);
int			check_foodlimit(t_philosophers_env *env);
int			create_philosophers(t_philosophers_env *env);
void		threads_start(t_philosophers_env *env);
void		threads_join(t_philosophers_env *env);
void		*philosophers_routine(void *data);
int			philo_starving(t_philosopher *philo);
void		free_philosophers(t_philosophers_env *env);
void		*scheduler_routine(void *data);

int			take_chopstik(t_philosopher *philo);
void		eating(t_philosopher *philo);
void		sleeping(t_philosopher *philo);
void		my_sleep(int time, t_philosopher *philo);
int			is_dead(t_philosophers_env *env);
int			philosopher_is_dead(t_philosopher *philosophers);
#endif