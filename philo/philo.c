/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-fati <dde-fati@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 22:58:20 by dde-fati          #+#    #+#             */
/*   Updated: 2024/06/29 17:33:26 by dde-fati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*long int	get_current_time_milisec(t_data *data)
{

}*/

int	init_data(t_data **data)
{
	*data = malloc(sizeof(t_data));
	if (gettimeofday(&(*data)->time, NULL) == -1)
		exit_error(4, *data);
	pthread_mutex_init(&(*data)->mutex, NULL);
	(*data)->num = 0;
	(*data)->cur_time = 0;
	return (EXIT_SUCCESS);
}

void	*routine(void *arg)
{
	t_data			*data;

	data = (t_data *)arg;
	printf("%ld Philosopher %d is eating\n", data->time.tv_sec, data->num);
	printf("%ld Philosopher %d is sleeping\n", data->time.tv_sec, data->num);
	printf("%ld Philosopher %d is thinking\n", data->time.tv_sec, data->num);
	pthread_mutex_unlock(&data->mutex);
	return (NULL);
}

int	main(void)
{
	pthread_t		threads[3];
	t_data			*data;
	int				i;

	if (init_data(&data) == 1)
		return (EXIT_FAILURE);
	while (data->num < 3)
	{
		pthread_mutex_lock(&data->mutex);
		if (pthread_create(&threads[data->num], NULL, &routine, data) != 0)
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
