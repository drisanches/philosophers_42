/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-fati <dde-fati@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 23:17:48 by dde-fati          #+#    #+#             */
/*   Updated: 2024/10/07 23:07:30 by dde-fati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

long	current_time_ms(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return (exit_error("Fail to get current time\n"));
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	print_message(long time, t_philo *philo, char *action)
{
	if (!check_others_death(philo->data))
	{
		pthread_mutex_lock(&philo->data->check_print);
		if (!check_others_death(philo->data))
			printf("%ld %d %s\n", time - philo->data->start_time,
				philo->id + 1, action);
		pthread_mutex_unlock(&philo->data->check_print);
	}
}

int	exit_error(char *error)
{
	printf("%s\n", error);
	return (EXIT_FAILURE);
}
