/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-fati <dde-fati@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 13:50:42 by  rleite-s         #+#    #+#             */
/*   Updated: 2024/10/07 23:32:03 by dde-fati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philos(t_philo *philo, int num_philos, t_data *data)
{
	int	i;

	i = 0;
	while (i < num_philos)
	{
		if (num_philos > 1 && i == 0)
			philo[i].left_fork = num_philos - 1;
		else
			philo[i].left_fork = i - 1;
		philo[i].right_fork = i;
		philo[i].id = i;
		philo[i].meals_left = data->num_meals;
		philo[i].last_meal = current_time_ms();
		philo[i++].data = data;
	}
}

void	init_mutexes(t_data *data, int num_philos)
{
	int	i;

	pthread_mutex_init(&data->check_death, 0);
	pthread_mutex_init(&data->check_meals, 0);
	pthread_mutex_init(&data->check_print, 0);
	pthread_mutex_init(&data->check_is_eating, 0);
	pthread_mutex_init(&data->check_is_dead, 0);
	i = 0;
	while (i < num_philos)
		pthread_mutex_init(&data->forks[i++], 0);
}

void	init_data(char **args, t_data *data)
{
	data->num_philos = ft_atol(args[1]);
	data->death_time = ft_atol(args[2]);
	data->eat_time = ft_atol(args[3]);
	data->sleep_time = ft_atol(args[4]);
	data->num_meals = -1;
	if (args[5])
		data->num_meals = ft_atol(args[5]);
	data->is_dead = 0;
	data->is_finished = 0;
}

int	init_all(char **args)
{
	t_data	data;
	t_philo	*philo;
	int		num_philos;

	num_philos = ft_atol(args[1]);
	philo = (t_philo *) malloc(num_philos * sizeof(t_philo));
	if (!philo)
		return (12); // porque 12?
	data.forks = (pthread_mutex_t *) malloc(num_philos * sizeof(pthread_mutex_t));
	if (!data.forks)
	{
		free(philo);
		return (12);
	}
	init_data(args, &data);
	init_philos(philo, num_philos, &data);
	init_mutexes(&data, num_philos);
	data.start_time = current_time_ms();
	create_threads(philo, num_philos);
	monitor(&data, philo, num_philos); 
	destroy_mutexes(&data, philo, num_philos);
	return (EXIT_SUCCESS);
}
