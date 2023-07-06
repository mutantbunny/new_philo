/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 23:17:38 by gmachado          #+#    #+#             */
/*   Updated: 2023/07/06 06:55:24 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_error	handle_error(t_params *pars, t_error err)
{
	const char	*err_str[] = {
		"OK",
		"Parameter error",
		"Memory allocation error",
		"Not a positive integer",
		"Mutex initialization error",
		"Thread initialization error",
		"Philosopher got to an invalid state"
	};

	printf("Error no. %d: %s\n", err, err_str[err]);
	cleanup(pars);
	return (err);
}

t_error	cleanup(t_params *pars)
{
	int	i;
	i = 0;
	while (i < pars->num_philos)
		pthread_mutex_destroy(&(pars->philos + i++)->meal_mtx);
	pthread_mutex_destroy(&pars->print_mtx);
	pthread_mutex_destroy(&pars->dinner_over_mtx);
	pthread_mutex_destroy(&pars->must_eat_mtx);
	free(pars->philos);
	free(pars->forks);
	return (OK);
}
