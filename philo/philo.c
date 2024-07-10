/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-fati <dde-fati@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 22:58:20 by dde-fati          #+#    #+#             */
/*   Updated: 2024/07/10 00:33:36 by dde-fati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	alloc_data(t_data *data)
{
	data->threads = malloc(sizeof(pthread_t) * data->num_philos);
	if (!data->threads)
		return(exit_error("Failed to malloc threads", data));
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->forks)
		return(exit_error("Failed to malloc forks", data));
	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!data->philos)
		return(exit_error("Failed to malloc philosophers", data));
	return (EXIT_SUCCESS);
}

int	init_foks(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_philos)
		pthread_mutex_init(&data->forks[i], NULL);
	i = 0;
	data->philos[0].left_fork = &data->forks[0];
	data->philos[0].right_fork = &data->forks[data->num_philos - 1];
	while (++i < data->num_philos)
	{
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[i - 1];
	}
	return (EXIT_SUCCESS);
}

int	init_data(t_data *data, char **argv)
{
	data = malloc(sizeof(t_data));
	if (!data)
		return (EXIT_FAILURE);
	data->num_philos = (int)ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	if (argv[5])
		data->num_meals = (int)ft_atol(argv[5]);
	else
		data->num_meals = 0;
	if (data->num_philos <= 0 || data->num_philos > 200 || data->time_to_die < 0 
		|| data->time_to_eat < 0 || data->time_to_sleep < 0)
		return(EXIT_FAILURE);
	data->start_time = current_time_ms();
	data->is_dead = 0;
	data->is_finished = 0;
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->lock, NULL);
	return (EXIT_SUCCESS);
}

void	init_philos(t_data *data)
{
	int	i;
	
	i = -1;
	while (++i < data->num_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].eat_count = 0;
		data->philos[i].is_eating = 0;
		data->philos[i].status = 0;
		data->philos[i].time_to_die = data->time_to_die;
		data->philos[i].data = data;
		pthread_mutex_init(&data->philos[i].lock, NULL);
		
	}
}
int	init_all(t_data *data, char **argv)
{
	if (init_data(data, argv))
		return(EXIT_FAILURE);
	if (alloc_data(data))
		return(EXIT_FAILURE);
	if (init_forks(data))
		return(EXIT_FAILURE);
	init_philos(data);
	return (EXIT_SUCCESS);
}

int	init_threads(t_data *data)
{
	pthread_t	t0;
	int			i;

	data->start_time = current_time_ms();
	if (data->num_meals > 0)
	{
		if (pthread_create(t0, NULL, &monitor, data->philos[0]))
			return (exit_error("Failed to create thread", data));
	}
	i = -1;
	while (++i < data->num_philos)
	{
		if (pthread_create(data->threads[i], NULL, &routine, data))
			return (exit_error("Failed to create thread", data));
	}
	i = -1;
	while (++i < data->num_philos)
	{
		if (pthread_join(data->threads[i], NULL))
			return (exit_error("Failed to join thread", data));
	}
}

int	check_args(int argc, char **argv)
{
	long int	nbr;
	int			i;
	
	if (argc < 5 || argc > 6)
		return (EXIT_FAILURE);
	i = 0;
	while (++i < argc)
	{
		nbr = ft_atol(argv[i]);
		if (!ft_isdigit(argv[i]) || nbr > INT_MAX || nbr < 0)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}


void	*routine(void *arg)
{
	t_data			*data;

	data = (t_data *)arg;
	pthread_mutex_lock(&data->print);
	printf("%ld Philosopher %d is eating\n", data->start_time, data->num_philos);
	printf("%ld Philosopher %d is sleeping\n", elapsed_time_ms(data->start_time), data->num);
	printf("%ld Philosopher %d is thinking\n", elapsed_time_ms(data->start_time), data->num);
	pthread_mutex_unlock(&data->print);
	return (NULL);
}

int	one_philo_routine(t_data *data)
{
	data->start_time = current_time_ms();
	if (pthread_create(&data->threads[0], NULL, &routine, &data->philos[0]))
		return (exit_error("Failed to create thread", data));
	pthread_detach(data->threads[0]);
	while (data->is_dead == 0)
		ft_usleep(0);
	clear(data); // --> criar função pra dar free na struct
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_data			*data;
	t_philo			*philos;
	int				i;

	if (check_args(argc, argv))
		return (exit_error("Invalid arguments", NULL));
	if (init_all(data, argv))
		return (exit_error("Failed to init data", NULL));
	if (data->num_philos == 1)
		return(one_philo_routine(&data));
	
	pthread_mutex_destroy(&data->print);
	free(data);
	return (EXIT_SUCCESS);
}
