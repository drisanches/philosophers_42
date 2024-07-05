/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-fati <dde-fati@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 22:58:30 by dde-fati          #+#    #+#             */
/*   Updated: 2024/07/05 00:56:16 by dde-fati         ###   ########.fr       */
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

typedef struct s_philo
{
	t_data			*data;
	pthread_t		t0;
	int				id;
	int				status;
	int				eat_count;
	int				is_eating;
	long long int	time_to_die;
	pthread_mutex_t	*lock;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}					t_philo;

typedef struct s_data
{
	int				num_philos;
	int				num_meals;
	int				is_dead;
	int				is_finished;
	long long int	time_to_eat;
	long long int	time_to_sleep;
	long long int	time_to_die;
	long long int	start_time;
	pthread_t		*threads;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	lock;
}					t_data;

/*Time Functions*/
long long int	current_time_ms(void);
long long int	elapsed_time_ms(long long int start_time);
int				msleep(long long int time_in_ms);

/*Error Functions*/
int				exit_error(char *msg, t_data *data);

/*Utils*/
int				ft_isdigit(int c);
long int		ft_atol(const char *nptr);

#endif