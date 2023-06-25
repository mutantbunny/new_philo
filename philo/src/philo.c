/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 22:12:16 by gmachado          #+#    #+#             */
/*   Updated: 2023/06/25 07:57:46 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_error	print_usage_msg(char *name);
static t_error	init_threads(t_params *pars);

int	main(int argc, char *argv[])
{
	t_params	pars;
	int			idx;
	t_error		err;

	if (get_args(&pars, argc, argv))
		return (print_usage_msg(char *name));
	err = init_parameters(&pars);
	if (err)
		return (handle_error(err, pars));
	err = init_philos(&pars);
	if (err)
		return (handle_error(err, pars));
	err = init_threads(&pars);
	if (err)
		return (handle_error(err, pars));
	idx = 0;
	while (idx < pars->num_philos)
		pthread_join(pars.philos[idx++].thread, NULL);
	pthread_join(pars.check_death_thread, NULL);
	return (cleanup(pars));
}

static t_error	print_usage_msg(char *name)
{
	printf("Usage: %s number_of_philosophers " \
			"time_to_die time_to_eat " \
			"time_to_sleep " \
			"[number_of_times_each_philosopher_must_eat]\n" \
			"Parameters should be positive integers\n", name);
	return (ERR_PARAMS);
}

static t_error	init_threads(t_params *pars)
{
	int	idx;

	idx = 0;
	pars.start_ts = timestamp_in_ms();
	while (idx < pars->num_philos)
	{
		if (pthread_create((pars->philo + idx)->thread, NULL,
				philo_handler, pars->philo + idx))
			return (ERR_THREAD);
		++idx;
	}
	if (pthread_create(pars->check_death_thread, NULL,
			check_death_handler, pars))
		return (ERR_THREAD);
	return (OK);
}
