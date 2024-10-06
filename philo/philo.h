/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-fati <dde-fati@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 22:58:30 by dde-fati          #+#    #+#             */
/*   Updated: 2024/10/06 19:36:12 by dde-fati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>

# define FORKS_TAKEN "has taken a fork"
# define SLEEPING "is sleeping"
# define EATING "is eating"
# define THINKING "is thinking"
# define DIED "died"

struct	s_data;

typedef struct s_philo
{
	struct s_data	*data;
	pthread_t		t1;
	int				id;
	int				status;
	int				eat_count;
	int				is_eating;
	long long int	time_to_die;
	pthread_mutex_t	lock;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}					t_philo;

typedef struct s_data
{
	int				num_philos;
	int				num_meals;
	int				is_dead;
	int				is_finished;
	long long int	eat_time;
	long long int	sleep_time;
	long long int	death_time;
	long long int	start_time;
	pthread_t		*threads;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	lock;
}					t_data;

/*Init Functions*/
int				alloc_data(t_data *data);
int				init_data(t_data *data, char **argv);
int				init_forks(t_data *data);
void			init_philos(t_data *data);
int				init_threads(t_data *data);
int				join_threads(t_data *data, pthread_t *monitor);

/*Time Functions*/
long long int	current_time_ms(void);
int				ft_usleep(__useconds_t time);

/*Threads Routines*/
int				one_philo(t_data *data);
void			*single_routine(void *args);
void			*routine(void *args);
void			*supervisor(void *args);
void			*monitor(void *args);
void			print_message(char *msg, t_philo *philo);
void			eat(t_philo *philo);
void			take_forks(t_philo *philo);
void			drop_forks(t_philo *philo);

/*Exit Functions*/
int				exit_error(char *msg, t_data *data);
void			clear_data(t_data *data);

/*Utils*/
int				ft_isdigit(int c);
long int		ft_atol(const char *nptr);
int				ft_strcmp(const char *s1, const char *s2);

#endif