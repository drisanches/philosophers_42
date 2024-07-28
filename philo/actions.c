/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-fati <dde-fati@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 16:59:54 by dde-fati          #+#    #+#             */
/*   Updated: 2024/07/28 19:14:20 by dde-fati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print_message(FORKS_TAKEN, philo);
	pthread_mutex_lock(philo->left_fork);
	print_message(FORKS_TAKEN, philo);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	print_message(SLEEPING, philo);
	ft_usleep(philo->data->sleep_time);
}

void	eat(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(&philo->lock);
	philo->is_eating = 1;
	philo->time_to_die = current_time_ms() + philo->data->death_time;
	print_message(EATING, philo);
	philo->eat_count++;
	ft_usleep(philo->data->eat_time);
	philo->is_eating = 0;
	pthread_mutex_unlock(&philo->lock);
	drop_forks(philo);
}