/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 22:12:16 by gmachado          #+#    #+#             */
/*   Updated: 2023/07/04 06:57:32 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_error	print_usage_msg(char *name);
static t_error	init_structs(t_params *pars, int argc, char **argv);

int	main(int argc, char *argv[])
{
	t_params	pars;
	int			idx;
	t_error		err;

	err = init_structs(&pars, argc, argv);
	if (err != OK)
		return (err);
	idx = -1;
	pars.start_ts = timestamp_in_ms();
	while (++idx < pars.num_philos)
	{
		if (pthread_create(&(pars.philos[idx].thread), NULL,
				philo_handler, pars.philos + idx))
			return (handle_error(&pars, ERR_THREAD));
	}
	if (pthread_create(&pars.check_death_thread, NULL,
			check_death_handler, &pars))
		return (handle_error(&pars, ERR_THREAD));
	idx = 0;
	while (idx < pars.num_philos)
		pthread_join(pars.philos[idx++].thread, NULL);
	pthread_join(pars.check_death_thread, NULL);
	return (cleanup(&pars));
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

static t_error	init_structs(t_params *pars, int argc, char **argv)
{
	t_error	err;

	if (get_args(pars, argc, argv))
		return (print_usage_msg(argv[0]));
	err = init_parameters(pars);
	if (err)
		return (handle_error(pars, err));
	err = init_philos(pars);
	if (err)
		return (handle_error(pars, err));
	return (OK);
}
