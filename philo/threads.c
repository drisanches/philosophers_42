/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-fati <dde-fati@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 13:54:55 by  rleite-s         #+#    #+#             */
/*   Updated: 2024/10/07 23:36:57 by dde-fati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	set_last_meal(philo);
	while (philo->meals_left && !check_others_death(philo->data))
	{
		try_to_eat(philo);
		if (philo->data->num_philos == 1)
		{
			usleep(philo->data->death_time * 1000);
			print_message(current_time_ms(), philo, DIED);
			break ;
		}
		if (philo->meals_left && !check_others_death(philo->data))
			sleep_action(philo);
		if (philo->meals_left && !check_others_death(philo->data))
			think_action(philo);
	}
	update_is_finished(philo);
	return (NULL);
}

void	create_threads(t_philo *philo, int num_philos)
{
	int	i;

	i = 0;
	while (i < num_philos)
	{
		pthread_create(&philo[i].thread, NULL, routine, &philo[i]);
		i++;
	}
}

void	destroy_mutexes(t_data *data, t_philo *philo, int num_philos)
{
	int	i;

	i = 0;
	while (i < num_philos)
		pthread_join(philo[i++].thread, 0);
	i = 0;
	while (i < num_philos)
		pthread_mutex_destroy(&data->forks[i++]);
	pthread_mutex_destroy(&data->check_death);
	pthread_mutex_destroy(&data->check_is_eating);
	pthread_mutex_destroy(&data->check_print);
	pthread_mutex_destroy(&data->check_is_dead);
	free(philo);
	free(data->forks);
}
