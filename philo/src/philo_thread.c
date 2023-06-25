/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 05:03:09 by gmachado          #+#    #+#             */
/*   Updated: 2023/06/25 09:44:07 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_bool	eat(t_params *pars, t_philo *philo);
static t_bool	eat_alone(t_params *pars, t_philo *philo);
static t_bool	go_sleep(t_params *pars, t_philo *philo);
static t_bool	think(t_params *pars, t_philo *philo);

void	*philo_handler(void *arg)
{
	t_philo			*philo;
	t_params		*pars;

	philo = arg;
	pars = philo->pars;
	while (TRUE)
	{
		if (eat(pars, philo) || go_sleep(pars, philo) || think(pars, philo))
			return (NULL);
	}
	return (NULL);
}

static t_bool	eat(t_params *pars, t_philo *philo)
{
	if (get_dinner_over(pars))
		return (TRUE);
	if (pars->num_philos == 1)
		return (eat_alone(pars, philo));
	pthread_mutex_lock(philo->first_fork);
	pthread_mutex_lock(philo->second_fork);
	if (get_dinner_over(pars))
	{
		pthread_mutex_unlock(philo->first_fork);
		pthread_mutex_unlock(philo->second_fork);
		return (TRUE);
	}
	print_state(pars, philo->number, ST_GOT_FORK);
	print_state(pars, philo->number, ST_GOT_FORK);
	set_last_meal_timestamp(philo);
	print_state(pars, philo->number, ST_EATING);
	sleep_in_ms(pars->time_to_eat);
	update_remaining_meals(philo);
	pthread_mutex_unlock(philo->first_fork);
	pthread_mutex_unlock(philo->second_fork);
	return (FALSE);
}

static t_bool	go_sleep(t_params *pars, t_philo *philo)
{
	if (get_dinner_over(pars))
		return (TRUE);
	print_state(pars, philo->number, ST_SLEEPING);
	sleep_in_ms(pars->time_to_sleep);
	return (FALSE);
}

static t_bool	think(t_params *pars, t_philo *philo)
{
	if (get_dinner_over(pars))
		return (TRUE);
	print_state(pars, philo->number, ST_THINKING);
	return (FALSE);
}

static t_bool	eat_alone(t_params *pars, t_philo *philo)
{
	print_state(pars, philo->number, ST_GOT_FORK);
	sleep_in_ms(pars->time_to_die * 2);
	return (TRUE);
}
