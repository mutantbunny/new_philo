/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 23:13:34 by gmachado          #+#    #+#             */
/*   Updated: 2023/06/25 07:55:33 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_error	get_args(t_param *pars, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (ERR_PARAMS);
	if (checked_atoi(argv[1], &pars->num_philos)
		|| checked_atoi(argv[2], &pars->time_to_die)
		|| checked_atoi(argv[3], &pars->time_to_eat)
		|| checked_atoi(argv[4], &pars->time_to_sleep))
		return (ERR_PARAMS);
	pars->num_meals = -1;
	if (argc == 6 && checked_atoi(argv[5], &pars->num_meals))
		return (ERR_PARAMS);
	return (OK);
}

t_error	init_parameters(t_param *pars)
{
	t_error	err;

	pars->forks = NULL;
	pars->philos = NULL;
	if (pthread_mutex_init(&pars->print_mtx, NULL)
		|| pthread_mutex_init(&pars->dinner_over_mtx, NULL)
		|| pthread_mutex_init(&pars->must_eat_mtx, NULL))
		return (ERR_MUTEX);
	err = init_forks(pars);
	if (err)
		return (err);
	pars->dinner_over = FALSE;
	pars->num_must_eat = pars->num_philos;
	return (OK);
}

t_error	init_forks(t_params *pars)
{
	pars->forks = malloc(num_forks * sizeof(**forks));
	if (pars->forks == NULL)
		return (ERR_ALLOC);
	idx = 0;
	while (idx < num_forks)
	{
		if (pthread_mutex_init(pars->forks + idx, NULL))
			return (ERR_MUTEX);
		++idx;
	}
	return (OK);
}

t_error	init_philos(t_params *pars)
{
	int		idx;
	t_philo	*philo;

	pars->philos = malloc(pars->num_philos * sizeof(**philos));
	if (pars->philos == NULL)
		return (ERR_ALLOC);
	idx = 0;
	while (idx < pars->num_philos)
	{
		philo = pars->philos + idx;
		if (pthread_mutex_init(&philo->last_meal_mtx, NULL))
			return (ERR_MUTEX);
		philo->number = idx;
		philo->first_fork = first_fork(pars, idx);
		philo->second_fork = second_fork(pars, idx);
		philo->pars = pars;
		philo->remaining_meals = pars->num_meals;
		set_last_meal_ts(philo);
		++idx;
	}
	return (OK);
}
