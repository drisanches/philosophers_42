/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-fati <dde-fati@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 13:38:23 by  rleite-s         #+#    #+#             */
/*   Updated: 2024/10/07 19:56:40 by dde-fati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	think_action(t_philo *philo)
{
	print_message(current_time_ms(), philo, THINKING);
	usleep(999);
}

void	sleep_action(t_philo *philo)
{
	print_message(current_time_ms(), philo, SLEEPING);
	usleep(philo->data->sleep_time * 1000);
}

void	eat_action(t_philo *philo)
{
	set_last_meal(philo);
	print_message(current_time_ms(), philo, EATING);
	if (philo->meals_left > 0)
		philo->meals_left--;
	usleep(philo->data->eat_time * 1000);
}

void	try_to_eat(t_philo *philo)
{
	if (philo->id & 1)
	{
		lock_fork(philo, philo->left_fork);
		lock_fork(philo, philo->right_fork);
	}
	else
	{
		lock_fork(philo, philo->right_fork);
		lock_fork(philo, philo->left_fork);
	}
	if (philo->left_fork >= 0 && philo->right_fork >= 0
		&& !check_others_death(philo->data))
		eat_action(philo);
	unlock_fork(philo, philo->left_fork);
	unlock_fork(philo, philo->right_fork);
}
