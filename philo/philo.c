/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-fati <dde-fati@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 22:58:20 by dde-fati          #+#    #+#             */
/*   Updated: 2024/07/21 19:20:12 by dde-fati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_all(t_data **data, char **argv)
{
	if (init_data(data, argv))
		return(EXIT_FAILURE);
	if (alloc_data(*data))
		return(EXIT_FAILURE);
	if (init_forks(*data))
		return(EXIT_FAILURE);
	init_philos(*data);
	return (EXIT_SUCCESS);
}

int	check_args(int argc, char **argv)
{
	long int	nbr;
	int			i;
	int			j;
	
	if (argc < 5 || argc > 6)
		return (EXIT_FAILURE);
	i = 0;
	while (++i < argc)
	{
		nbr = ft_atol(argv[i]);
		j = -1;
		while (argv[i][++j])
		{	
			if (!ft_isdigit(argv[i][j]) || nbr > INT_MAX || nbr < 0)
				return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_data			*data;

	if (check_args(argc, argv))
		return (exit_error("Invalid arguments", NULL));
	data = NULL;
	if (init_all(&data, argv))
		return (exit_error("Failed to init data", NULL));
	if (data->num_philos == 1)
		return(one_philo_routine(data));
	if (init_threads(data))
		return (EXIT_FAILURE);
	clear_data(data);
	return (EXIT_SUCCESS);
}
