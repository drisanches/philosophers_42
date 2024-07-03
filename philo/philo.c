/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-fati <dde-fati@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 22:58:20 by dde-fati          #+#    #+#             */
/*   Updated: 2024/07/03 00:27:10 by dde-fati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(int argc, char **argv, t_data *data)
{
	long int	nbr;
	int			i;
	
	if (argc != 5 && argc != 6)
		return (EXIT_FAILURE);
	i = 0;
	while (++i < argc)
	{
		nbr = ft_atol(argv[i]);
		if (!ft_isdigit(argv[i]) || nbr > INT_MAX || nbr < 0)
			return (EXIT_FAILURE);
	}
	data = malloc(sizeof(t_data));
	if (!data)
		return (EXIT_FAILURE);
	data->num_philos = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	if (argv[5])
		data->num_meals = ft_atol(argv[5]);
	else
		data->num_meals = 0;
	return (EXIT_SUCCESS);
}

void	init_data(t_data **data)
{
	(*data)->start_time = current_time_ms();
	pthread_mutex_init(&(*data)->mutex, NULL);
}

void	init_philos(t_philo **philos, t_data *data)
{
	int	i;
	
	*philos = malloc(data->num_philos * sizeof(t_philo));
	if (!philos)
		return (EXIT_FAILURE);
	i = -1;
	while (++i < data->num_philos)
	{
		(*philos)[i].id = i + 1;
		(*philos)[i].left_fork = malloc(sizeof(pthread_mutex_t));
		(*philos)[i].right_fork = malloc(sizeof(pthread_mutex_t));
		(*philos)[i].thread = malloc(sizeof(pthread_t));
		(*philos)[i].data = data;
	}
}

void	*routine(void *arg)
{
	t_data			*data;

	data = (t_data *)arg;
	pthread_mutex_lock(&data->mutex);
	printf("%ld Philosopher %d is eating\n", data->start_time, data->num_philos);
	printf("%ld Philosopher %d is sleeping\n", elapsed_time_ms(data->start_time), data->num);
	printf("%ld Philosopher %d is thinking\n", elapsed_time_ms(data->start_time), data->num);
	pthread_mutex_unlock(&data->mutex);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_data			*data;
	t_philo			*philos;
	int				i;

	if (!check_args(argc, argv, data))
		return (exit_error(-1, NULL));
	init_data(&data);
	init_philos(&philos, data);
	i = -1;
	while (++i < data->num_philos)
	{
		if (pthread_create(philos->thread[i], NULL, &routine, data) != 0)
			return (exit_error(1, data));
	}
	i = -1;
	while (++i < data->num_philos)
	{
		if (pthread_join(philos->thread[i], NULL) != 0)
			return (exit_error(2, data));
	}
	pthread_mutex_destroy(&data->mutex);
	free(data);
	return (EXIT_SUCCESS);
}
