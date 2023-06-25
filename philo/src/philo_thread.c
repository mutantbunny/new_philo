/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 05:03:09 by gmachado          #+#    #+#             */
/*   Updated: 2023/06/25 17:23:35 by eandre-f         ###   ########.fr       */
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
	if (pars->num_philos == 1)
	{
		eat_alone(pars, philo);
		return (NULL);
	}
	while (TRUE)
	{
		if (eat(pars, philo))
			return (NULL);
		if (go_sleep(pars, philo))
			return (NULL);
		if (think(pars, philo))
			return (NULL);
	}
	return (NULL);
}

static t_bool	eat(t_params *pars, t_philo *philo)
{
	if (get_dinner_over(pars))
		return (TRUE);
	pthread_mutex_lock(philo->first_fork);
	print_state(pars, philo->number, ST_GOT_FORK);
	pthread_mutex_lock(philo->second_fork);
	if (get_dinner_over(pars))
	{
		pthread_mutex_unlock(philo->first_fork);
		pthread_mutex_unlock(philo->second_fork);
		return (TRUE);
	}
	print_state(pars, philo->number, ST_GOT_FORK);
	print_state(pars, philo->number, ST_EATING);
	set_last_meal_timestamp(philo);
	sleep_in_ms(pars->time_to_eat);
	// update_remaining_meals(philo);
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
