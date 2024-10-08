/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-fati <dde-fati@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 22:58:30 by dde-fati          #+#    #+#             */
/*   Updated: 2024/10/07 23:30:28 by dde-fati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <limits.h>

# define FORKS_TAKEN "has taken a fork"
# define SLEEPING "is sleeping"
# define EATING "is eating"
# define THINKING "is thinking"
# define DIED "died"

typedef struct s_data
{
	int				num_philos;
	int				death_time;
	int				eat_time;
	int				sleep_time;
	int				num_meals;
	int				is_dead;
	int				is_finished;
	long			start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	check_death;
	pthread_mutex_t	check_meals;
	pthread_mutex_t	check_print;
	pthread_mutex_t	check_time;
	pthread_mutex_t	check_is_eating;
	pthread_mutex_t	check_is_dead;
}					t_data;

typedef struct s_philo
{
	int				id;
	int				right_fork;
	int				left_fork;
	int				meals_left;
	long			last_meal;
	pthread_t		thread;
	t_data			*data;
}					t_philo;

// Init Functions
void	init_philos(t_philo *philo, int total, t_data *data);
void	init_mutexes(t_data *data, int total);
void	init_data(char **args, t_data *data);
int		init_all(char **args);

// Thread Functions
int		one_philo(t_philo *philo);
void	*single_routine(void *args);
void	create_threads(t_philo *philo, int num_philos);
void	*routine(void *arg);
void	destroy_mutexes(t_data *data, t_philo *philo, int total);

// Philo Actions
void	think_action(t_philo *philo);
void	sleep_action(t_philo *philo);
void	eat_action(t_philo *philo);
void	try_to_eat(t_philo *philo);

// Check Functions
int		check_own_death(t_philo *philo);
int		check_others_death(t_data *data);
void	update_death(t_data *data);
void	monitor(t_data *data, t_philo *philo, int total);
int		all_meals_completed(t_data *data, int total);
void	update_is_finished(t_philo *philo);
long	get_last_meal(t_philo *philo);
void	set_last_meal(t_philo *philo);

// Fork Functions
void	lock_fork(t_philo *philo, int fork_num);
void	unlock_fork(t_philo *philo, int fork_num);

// Utils
int		ft_isdigit(int c);
long	ft_atol(const char *nptr);
long	current_time_ms(void);
void	print_message(long time, t_philo *philo, char *action);
int		exit_error(char *error);

#endif