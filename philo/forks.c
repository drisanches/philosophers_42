/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-fati <dde-fati@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 13:42:05 by  rleite-s         #+#    #+#             */
/*   Updated: 2024/10/07 23:34:28 by dde-fati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lock_fork(t_philo *philo, int fork_num)
{
	if (fork_num >= 0)
	{
		pthread_mutex_lock(&philo->data->forks[fork_num]);
		print_message(current_time_ms(), philo, FORKS_TAKEN);
	}
}

void	unlock_fork(t_philo *philo, int fork_num)
{
	if (fork_num >= 0)
		pthread_mutex_unlock(&philo->data->forks[fork_num]);
}
