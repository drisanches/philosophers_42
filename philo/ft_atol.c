/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-fati <dde-fati@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 23:18:04 by dde-fati          #+#    #+#             */
/*   Updated: 2024/07/02 23:18:04 by dde-fati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_issignal(char c)
{
	if (c == '-' || c == '+')
		return (1);
	return (0);
}

static int	ft_isspace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

long int	ft_atol(const char *nptr)
{
	long int	result;
	int			i;
	int			is_negative;

	is_negative = 0;
	result = 0;
	i = 0;
	while (ft_isspace(nptr[i]))
		i++;
	if (ft_issignal(nptr[i]))
	{
		if (nptr[i] == '-')
			is_negative = 1;
		i++;
	}
	while (ft_isdigit(nptr[i]))
	{
		result = (result * 10) + (nptr[i] - '0');
		i++;
	}
	if (is_negative)
		result *= -1;
	return (result);
}
