/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-fati <dde-fati@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 22:38:25 by dde-fati          #+#    #+#             */
/*   Updated: 2024/07/21 17:28:09 by dde-fati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long int	current_time_ms(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return (exit_error("Fail to get current time", NULL));
	return (time.tv_sec * 1000 + time.tv_sec / 1000);
}

long long int	elapsed_time_ms(long long int start_time)
{
	return ((current_time_ms() - start_time));
}

int	msleep(long long int time_in_ms)
{
	return (usleep(time_in_ms * 1000));
}

int	ft_usleep(__useconds_t time)
{
	long long int	start;

	start = current_time_ms();
	while (current_time_ms() - start < time)
		usleep(time / 10);
	return (EXIT_SUCCESS);
}