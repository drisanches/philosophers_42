/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-fati <dde-fati@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 22:58:20 by dde-fati          #+#    #+#             */
/*   Updated: 2024/06/25 22:51:24 by dde-fati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_data(t_data **data)
{
	*data = malloc(sizeof(t_data));
	pthread_mutex_init(&(*data)->mutex, NULL);
	(*data)->num = 0;
}

void	*thread_function(void *arg)
{
	t_data		*data;
	
	data = (t_data *)arg;
	printf("This is thread: %d\n", data->num);
	pthread_mutex_unlock(&data->mutex);
	return (NULL);
}

int	main(void)
{
	pthread_t		threads[3];
	t_data			*data;
	int				i;

	init_data(&data);
	while (data->num < 3)
	{
		pthread_mutex_lock(&data->mutex);
		if (pthread_create(&threads[data->num], NULL, &thread_function, data) != 0)
			return (exit_error(1, data));
		data->num++;
	}
	i = 0;
	while (i < 3)
	{
		if (pthread_join(threads[i], NULL) != 0)
			return (exit_error(2, data));
		i++;
	}
	pthread_mutex_destroy(&data->mutex);
	free(data);
	return (EXIT_SUCCESS);
}
