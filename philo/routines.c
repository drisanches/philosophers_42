/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-fati <dde-fati@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:28:16 by dde-fati          #+#    #+#             */
/*   Updated: 2024/10/06 17:41:32 by dde-fati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(char *msg, t_philo *philo)
{
	long long int	time;

	pthread_mutex_lock(&philo->data->print);
	time = current_time_ms() - philo->data->start_time;
	pthread_mutex_lock(&philo->data->lock);
	if (ft_strcmp(DIED, msg) == 0 && philo->data->is_dead == 0)
	{
		printf("%llu %d %s\n", time, philo->id, msg);
		philo->data->is_dead = 1;
	}
	else if (!philo->data->is_dead)
	{
		printf("%llu %d %s\n", time, philo->id, msg);
	}
	pthread_mutex_unlock(&philo->data->lock);
	pthread_mutex_unlock(&philo->data->print);
}

void	*monitor(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	while (1)
	{
		pthread_mutex_lock(&philo->data->lock);
		if (philo->data->is_finished >= philo->data->num_philos)
			philo->data->is_dead = 1;
		if (philo->data->is_dead)
		{
			pthread_mutex_unlock(&philo->data->lock);
			break ;
		}
		pthread_mutex_unlock(&philo->data->lock);
	}
	print_message("estamos aqui monitor\n", philo);
	//printf("estamos aqui monitor\n");
	return ((void *)EXIT_SUCCESS);
}

/*void	*supervisor(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	pthread_mutex_lock(&philo->data->lock);
	while (philo->data->is_dead == 0)
	{
		pthread_mutex_unlock(&philo->data->lock);
		pthread_mutex_lock(&philo->lock);
		if (current_time_ms() >= philo->time_to_die && philo->is_eating == 0)
		{
			pthread_mutex_lock(&philo->data->lock);
			print_message(DIED, philo);
			pthread_mutex_unlock(&philo->data->lock);
		}
		if (philo->eat_count == philo->data->num_meals)
		{
			pthread_mutex_lock(&philo->data->lock);
			philo->data->is_finished++;
			philo->eat_count++;
			pthread_mutex_unlock(&philo->data->lock);
		}
		pthread_mutex_unlock(&philo->lock);
		pthread_mutex_lock(&philo->data->lock);
	}
	return ((void *)EXIT_SUCCESS);
}*/

void	*supervisor(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	while (1)
	{
		pthread_mutex_lock(&philo->data->lock);
		if (philo->data->is_dead == 0)
		{
			pthread_mutex_unlock(&philo->data->lock);
			pthread_mutex_lock(&philo->lock);
			if (current_time_ms() >= philo->time_to_die && philo->is_eating == 0)
			{
				pthread_mutex_unlock(&philo->lock);
				print_message(DIED, philo);
				break ;
			}
			else if (philo->eat_count == philo->data->num_meals)
			{
				pthread_mutex_lock(&philo->data->lock);
				philo->data->is_finished++;
				philo->eat_count++;
				pthread_mutex_unlock(&philo->data->lock);
			}
			pthread_mutex_unlock(&philo->lock);
		}
	}
	print_message("estamos aqui super\n", philo);
	//printf("estamos aqui super\n");
	return ((void *)EXIT_SUCCESS);
}

void	*routine(void *args)
{
	t_philo			*philo;

	philo = (t_philo *)args;
	philo->time_to_die = philo->data->death_time + current_time_ms();
	if (pthread_create(&philo->t1, NULL, &supervisor, philo) != 0)
		return ((void *)EXIT_FAILURE);
	while (1)
	{
		pthread_mutex_lock(&philo->data->lock);
		if (philo->data->is_dead)
		{
			pthread_mutex_unlock(&philo->data->lock);
			break ;
		}
		pthread_mutex_unlock(&philo->data->lock);
		eat(philo);
		print_message(THINKING, philo);
	}
	print_message("estamos aqui routine\n", philo);
	if (pthread_join(philo->t1, NULL) != 0)
		return ((void *)EXIT_FAILURE);
	return (NULL);
}

/*void	*routine(void *args)
{
	t_philo			*philo;

	philo = (t_philo *)args;
	philo->time_to_die = philo->data->death_time + current_time_ms();
	if (pthread_create(&philo->t1, NULL, &supervisor, philo) != 0)
		return ((void *)EXIT_FAILURE);
	pthread_mutex_lock(&philo->data->lock);
	while (philo->data->is_dead == 0)
	{
		pthread_mutex_unlock(&philo->data->lock);
		eat(philo);
		print_message(THINKING, philo);
	}
	if (pthread_join(philo->t1, NULL) != 0)
		return ((void *)EXIT_FAILURE);
	return (NULL);
}*/

void	*single_routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	pthread_mutex_lock(philo->right_fork);
	print_message(FORKS_TAKEN, philo);
	ft_usleep(philo->time_to_die);
	pthread_mutex_unlock(philo->right_fork);
	print_message(DIED, philo);
	return (NULL);
}

int	one_philo(t_data *data)
{
	data->start_time = current_time_ms();
	if (pthread_create(&data->threads[0], NULL,
			&single_routine, &data->philos[0]) != 0)
		return (exit_error("Failed to create thread", data));
	pthread_detach(data->threads[0]);
	while (data->is_dead == 0)
		ft_usleep(0);
	clear_data(data);
	return (EXIT_SUCCESS);
}
