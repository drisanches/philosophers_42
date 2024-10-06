/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-fati <dde-fati@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 17:40:34 by dde-fati          #+#    #+#             */
/*   Updated: 2024/10/06 19:36:29 by dde-fati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	alloc_data(t_data *data)
{
	data->threads = malloc(sizeof(pthread_t) * data->num_philos);
	if (!data->threads)
		return (exit_error("Failed to malloc threads", data));
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->forks)
		return (exit_error("Failed to malloc forks", data));
	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!data->philos)
		return (exit_error("Failed to malloc philosophers", data));
	return (EXIT_SUCCESS);
}

int	init_forks(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_philos)
		pthread_mutex_init(&data->forks[i], NULL);
	i = 0;
	data->philos[0].left_fork = &data->forks[0];
	data->philos[0].right_fork = &data->forks[data->num_philos - 1];
	while (++i < data->num_philos)
	{
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[i - 1];
	}
	return (EXIT_SUCCESS);
}

int	init_data(t_data *data, char **argv)
{
	data->num_philos = (int)ft_atol(argv[1]);
	data->death_time = ft_atol(argv[2]);
	data->eat_time = ft_atol(argv[3]);
	data->sleep_time = ft_atol(argv[4]);
	if (argv[5])
		data->num_meals = (int)ft_atol(argv[5]);
	else
		data->num_meals = 0;
	if (data->num_philos <= 0 || data->num_philos > 200 || data->death_time < 0
		|| data->eat_time < 0 || data->sleep_time < 0)
		return (EXIT_FAILURE);
	data->start_time = current_time_ms();
	data->is_dead = 0;
	data->is_finished = 0;
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->lock, NULL);
	return (EXIT_SUCCESS);
}

void	init_philos(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].eat_count = 0;
		data->philos[i].is_eating = 0;
		data->philos[i].status = 0;
		data->philos[i].time_to_die = data->death_time;
		data->philos[i].data = data;
		pthread_mutex_init(&data->philos[i].lock, NULL);
	}
}

int	join_threads(t_data *data, pthread_t *monitor)
{
	int	i;

	if (data->num_meals > 0)
	{
		if (pthread_join(*monitor, NULL) != 0)
			return (exit_error("Failed to join thread", data));
	}
	i = -1;
	while (++i < data->num_philos)
	{
		if (pthread_join(data->threads[i], NULL))
			return (exit_error("Failed to join thread", data));
	}
	return (EXIT_SUCCESS);
}

int	init_threads(t_data *data)
{
	pthread_t	monitor_thread;
	int			i;

	data->start_time = current_time_ms();
	if (data->num_meals > 0)
	{
		if (pthread_create(&monitor_thread, NULL, &monitor, &data->philos[0]))
			return (exit_error("Failed to create thread", data));
	}
	i = -1;
	while (++i < data->num_philos)
	{
		if (pthread_create(&data->threads[i], NULL, &routine, &data->philos[i]))
			return (exit_error("Failed to create thread", data));
	}
	if (join_threads(data, &monitor_thread))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
