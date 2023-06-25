/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 05:03:09 by gmachado          #+#    #+#             */
/*   Updated: 2023/06/25 06:55:24 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

t_bool	eat(t_params *pars, t_philo *philo)
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
	print_state(pars, philo->num, ST_GOT_FORK);
	print_state(pars, philo->num, ST_GOT_FORK);
	print_state(pars, philo->num, ST_EATING);
	update_remaining_meals(philo);
	pthread_mutex_unlock(philo->first_fork);
	pthread_mutex_unlock(philo->second_fork);
	return (FALSE);
}

t_bool	go_sleep(t_params *pars, t_philo *philo)
{
	if (get_dinner_over(pars))
		return (TRUE);
	print_state(pars, philo->num, ST_SLEEPING);
	usleep(pars->time_to_sleep * 1000);
	return (FALSE);
}

t_bool	think(t_params *pars, t_philo *philo)
{
	if (get_dinner_over(pars))
		return (TRUE);
	print_state(pars, philo->num, ST_THINKING);
	return (FALSE);
}

t_bool	eat_alone(t_params *pars, t_philo *philo)
{
	print_state(pars, philo->num, ST_GOT_FORK);
	usleep(pars->time_to_die * 2000);
	return (TRUE);
}
