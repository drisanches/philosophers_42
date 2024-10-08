/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-fati <dde-fati@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 13:47:39 by  rleite-s         #+#    #+#             */
/*   Updated: 2024/10/07 20:12:00 by dde-fati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	update_death(t_data *data)
{
	pthread_mutex_lock(&data->check_death);
	data->is_dead++;
	pthread_mutex_unlock(&data->check_death);
}

int	check_own_death(t_philo *philo)
{
	int	dead;

	dead = 0;
	pthread_mutex_lock(&philo->data->check_is_dead);
	if (current_time_ms() - get_last_meal(philo) > philo->data->death_time)
	{
		if (!check_others_death(philo->data)
			&& current_time_ms() - get_last_meal(philo)
			> philo->data->death_time)
		{
			print_message(current_time_ms(), philo, DIED);
			update_death(philo->data);
		}
		dead = 1;
	}
	pthread_mutex_unlock(&philo->data->check_is_dead);
	return (dead);
}

int	check_others_death(t_data *data)
{
	int	dead;

	pthread_mutex_lock(&data->check_death);
	dead = data->is_dead;
	pthread_mutex_unlock(&data->check_death);
	return (dead);
}

void	monitor(t_data *data, t_philo *philo, int total)
{
	int	i;

	i = 0;
	while (!check_others_death(data) && !all_meals_completed(data, total))
	{
		if (check_own_death(&philo[i]))
			update_death(data);
		i++;
		if (i == total)
			i = 0;
		usleep(100);
	}
}
