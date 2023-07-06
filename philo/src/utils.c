/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 04:30:44 by gmachado          #+#    #+#             */
/*   Updated: 2023/07/04 06:50:06 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_fork	*first_fork(t_philo *philo)
{
	int	philo_number;

	philo_number = philo->number;
	if (philo_number % 2 == 0)
		return (philo->pars->forks + philo_number);
	return (philo->pars->forks + ((philo_number + 1)
			% philo->pars->num_philos));
}

t_fork	*second_fork(t_philo *philo)
{
	int	philo_number;

	if (philo->pars->num_philos == 1)
		return (NULL);
	philo_number = philo->number;
	if (philo_number % 2 == 0)
	{
		return (philo->pars->forks + ((philo_number + 1)
				% philo->pars->num_philos));
	}
	return (philo->pars->forks + philo_number);
}

void	print_state(t_params *pars, int idx, t_state state)
{
	long long	ts;

	ts = timestamp_in_ms() - pars->start_ts;
	pthread_mutex_lock(&pars->print_mtx);
	if (get_dinner_over(pars) == FALSE)
	{
		if (state == ST_THINKING)
			printf("%lld %d is thinking\n", ts, idx + 1);
		else if (state == ST_GOT_FORK)
			printf("%lld %d has taken a fork\n", ts, idx + 1);
		else if (state == ST_EATING)
			printf("%lld %d is eating\n", ts, idx + 1);
		else if (state == ST_SLEEPING)
			printf("%lld %d is sleeping\n", ts, idx + 1);
	}
	pthread_mutex_unlock(&pars->print_mtx);
}
