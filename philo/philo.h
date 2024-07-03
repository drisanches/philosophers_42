/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-fati <dde-fati@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 22:58:30 by dde-fati          #+#    #+#             */
/*   Updated: 2024/07/03 00:25:33 by dde-fati         ###   ########.fr       */
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

typedef struct s_data
{
	int				num_philos;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	int				num_meals;
	long long int	start_time;
	pthread_mutex_t	mutex;
}					t_data;

typedef struct s_philo
{
	int				id;
	t_data			*data;
	pthread_t		*thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}					t_philo;

/*Time Functions*/
long long int	current_time_ms(void);
long long int	elapsed_time_ms(long long int start_time);
int				msleep(long long int time_in_ms);

/*Error Functions*/
int				exit_error(int code, t_data *data);

/*Utils*/
int				ft_isdigit(int c);
long int		ft_atol(const char *nptr);

#endif