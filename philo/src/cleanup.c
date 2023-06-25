/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 23:17:38 by gmachado          #+#    #+#             */
/*   Updated: 2023/06/25 08:16:32 by gmachado         ###   ########.fr       */
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
	int	idx;

	pthread_mutex_destroy(&pars->print_mtx);
	pthread_mutex_destroy(&pars->dinner_over_mtx);
	idx = 0;
	while (idx < pars->num_philos)
		pthread_mutex_destroy(&(pars->philos + idx++)->last_meal_mtx);
	free(pars->philos);
	free(pars->forks);
	return (OK);
}
