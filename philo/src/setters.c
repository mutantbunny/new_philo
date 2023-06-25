/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 04:30:27 by gmachado          #+#    #+#             */
/*   Updated: 2023/06/25 06:47:19 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_last_meal_ts(t_philo *philo)
{
	pthread_mutex_lock(&philo->last_meal_mtx);
	philo->last_meal_ts = timestamp_in_ms();
	pthread_mutex_unlock(&philo->last_meal_mtx);
}

void	update_remaining_meals(t_philo *philo)
{
	t_bool		all_finished;
	t_params	*pars;

	pars = philo->pars;
	if (philo->remaining_meals < 0)
		return ;
	if (philo->remaining_meals > 0)
	{
		philo->remaining_meals--;
		return ;
	}
	pthread_mutex_lock(&pars->must_eat_mtx);
	if (pars->num_must_eat)
		pars->num_must_eat--;
	all_finished = (pars->num_must_eat == 0);
	pthread_mutex_unlock(&pars->must_eat_mtx);
	if (all_finished)
		end_dinner(pars);
}

void	end_dinner(t_params *pars)
{
	pthread_mutex_lock(&pars->dinner_over_mtx);
	pars->dinner_over = TRUE;
	pthread_mutex_unlock(&philo->dinner_over_mtx);
}
