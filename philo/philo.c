/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-fati <dde-fati@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 22:58:20 by dde-fati          #+#    #+#             */
/*   Updated: 2024/06/25 21:36:23 by dde-fati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t	mutex;

void	*thread_function(void *tid)
{
	long int	id;
	
	id = (long int)tid;
	printf("This is thread: %ld\n", id);
	pthread_mutex_unlock(&mutex);
	return (NULL);
}

int	main(void)
{
	pthread_t		threads[3];
	int				i;

	i = 0;
	pthread_mutex_init(&mutex, NULL);
	while (i < 3)
	{
		pthread_mutex_lock(&mutex);
		if (pthread_create(&threads[i], NULL, &thread_function, (void *)(long)i) != 0)
			return (exit_error(1));
		i++;
	}
	i = 0;
	while (i < 3)
	{
		if (pthread_join(threads[i], NULL) != 0)
			return (exit_error(2));
		i++;
	}
	pthread_mutex_destroy(&mutex);
	return (EXIT_SUCCESS);
}
