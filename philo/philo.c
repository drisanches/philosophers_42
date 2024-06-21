/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-fati <dde-fati@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 22:58:20 by dde-fati          #+#    #+#             */
/*   Updated: 2024/06/21 00:32:07 by dde-fati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*thread_function(void *tid)
{
	long int	id;
	
	id = (long int)tid;
	printf("This is thread: %ld\n", id);
}

int	main(void)
{
	pthread_t	tid0; // estrutura que define uma thread
	pthread_t	tid1;
	pthread_t	tid2;
	pthread_t	*pthreads[] = {&tid0, &tid1, &tid2};
	int			i;

	i = -1;
	while (++i < 3)
	{
		// inicializando a nova thread
		pthread_create(pthreads[i], NULL, thread_function, (void *)pthreads[i]);
		pthread_detach(*pthreads[i]);
	}
	pthread_exit(NULL); // espera a thread ser executada
	return (0);
}
