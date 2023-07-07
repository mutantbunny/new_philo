/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 04:30:27 by gmachado          #+#    #+#             */
/*   Updated: 2023/07/06 06:54:35 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_last_meal_timestamp(t_philo *philo)
{
	t_params	*pars;

	pars = philo->pars;
	pthread_mutex_lock(&philo->meal_mtx);
	philo->last_meal_ts = timestamp_in_ms();
	pthread_mutex_unlock(&philo->meal_mtx);
	if (philo->remaining_meals < 0)
		return ;
	if (philo->remaining_meals > 0)
		--(philo->remaining_meals);
	else
	{
		pthread_mutex_lock(&pars->must_eat_mtx);
		--(pars->num_must_eat);
		if (pars->num_must_eat < 0)
			end_dinner(pars);
		pthread_mutex_unlock(&pars->must_eat_mtx);
	}
}

void	end_dinner(t_params *pars)
{
	pthread_mutex_lock(&pars->dinner_over_mtx);
	pars->dinner_over = TRUE;
	pthread_mutex_unlock(&pars->dinner_over_mtx);
}

t_bool	get_dinner_over(t_params *pars)
{
	t_bool	result;

	pthread_mutex_lock(&pars->dinner_over_mtx);
	result = pars->dinner_over;
	pthread_mutex_unlock(&pars->dinner_over_mtx);
	return (result);
}

long long	get_last_meal_timestamp(t_philo *philo)
{
	long long	result;

	pthread_mutex_lock(&philo->meal_mtx);
	result = philo->last_meal_ts;
	pthread_mutex_unlock(&philo->meal_mtx);
	return (result);
}
