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
	// long long	time_to_think;

	// time_to_think = (pars->time_to_die
	// 	- (timestamp_in_ms() - get_last_meal_timestamp(philo))
	// 	- pars->time_to_eat) / 2;
	// if (time_to_think > 500)
	// 	time_to_think = 200;
	// else
	// 	time_to_think = 1;
	if (get_dinner_over(pars))
		return (TRUE);
	print_state(pars, philo->number, ST_THINKING);
	// sleep_in_ms(time_to_think);
	return (FALSE);

}

static t_bool	eat_alone(t_params *pars, t_philo *philo)
{
	print_state(pars, philo->number, ST_GOT_FORK);
	sleep_in_ms(pars->time_to_die * 2);
	return (TRUE);
}
