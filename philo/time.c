/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-fati <dde-fati@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 22:38:25 by dde-fati          #+#    #+#             */
/*   Updated: 2024/07/28 18:54:26 by dde-fati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long int	current_time_ms(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return (exit_error("Fail to get current time", NULL));
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	ft_usleep(__useconds_t time)
{
	long long int	start;

	start = current_time_ms();
	while ((current_time_ms() - start) < time)
		usleep(500);
	return (EXIT_SUCCESS);
}