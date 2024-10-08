/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_meals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-fati <dde-fati@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 14:03:05 by  rleite-s         #+#    #+#             */
/*   Updated: 2024/10/07 22:25:25 by dde-fati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_last_meal(t_philo *philo)
{
	long	last_meal;

	pthread_mutex_lock(&philo->data->check_is_eating);
	last_meal = philo->last_meal;
	pthread_mutex_unlock(&philo->data->check_is_eating);
	return (last_meal);
}

void	set_last_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->check_is_eating);
	philo->last_meal = current_time_ms();
	pthread_mutex_unlock(&philo->data->check_is_eating);
}

void	update_is_finished(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->check_meals);
	philo->data->is_finished++;
	pthread_mutex_unlock(&philo->data->check_meals);
}

int	all_meals_completed(t_data *data, int total)
{
	int	meals;

	pthread_mutex_lock(&data->check_meals);
	meals = data->is_finished;
	pthread_mutex_unlock(&data->check_meals);
	return (meals == total);
}
