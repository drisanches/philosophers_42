/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-fati <dde-fati@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 09:25:58 by  rleite-s         #+#    #+#             */
/*   Updated: 2024/10/07 22:40:49 by dde-fati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_args(int argc, char **argv)
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
	if (check_args(argc, argv))
		return (exit_error("Invalid arguments"));
	init_all(argv);
	return (EXIT_SUCCESS);
}
