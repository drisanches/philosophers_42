/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-fati <dde-fati@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 23:05:38 by dde-fati          #+#    #+#             */
/*   Updated: 2024/07/05 00:55:52 by dde-fati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	exit_error(char *msg, t_data *data)
{
	printf("%s\n", msg);	
	if (data)
		free(data);
	return (EXIT_FAILURE);
}
