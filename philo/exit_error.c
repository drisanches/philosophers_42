/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-fati <dde-fati@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 23:05:38 by dde-fati          #+#    #+#             */
/*   Updated: 2024/06/24 23:06:01 by dde-fati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	exit_error(int code)
{
	if (code = 1)
		printf("Failed to create thread\n");	
	else if (code = 2)
		printf("Failed to join thread\n");
	else if (code = 3)
		printf("Failed to detach thread\n");
	return (code);
}
