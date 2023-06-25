/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 04:30:44 by gmachado          #+#    #+#             */
/*   Updated: 2023/06/25 06:24:19 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_fork	*first_fork(t_params *pars, int idx)
{
	if (pars->philo->num % 2 == 0)
		return (pars->forks + idx);
	else
		return (pars->forks + ((idx + 1) % pars->num_philos));
}

t_fork	*second_fork(t_params *pars, int idx)
{
	if (pars->num_philos == 1)
		return (NULL);
	if (pars->philo->num % 2 == 0)
		return (pars->forks + ((idx + 1) % pars->num_philos));
	else
		return (pars->forks + idx);
}

void	print_state(t_params *pars, int idx, t_state state)
{
	pthread_mutex_lock(&pars->print_mutex);
	if (pars->get_sim_over() == FALSE)
	{
		ft_putnbr(timestamp_in_ms() - pars->start_ts);
		write(1, " ", 1);
		ft_putnbr((long long)idx + 1);
		if (state == ST_THINKING)
			write(1, " is thinking\n", 13);
		else if (state == ST_GOT_FORK)
			write(1, " has taken a fork\n", 18);
		else if (state == ST_EATING)
			write(1, " is eating\n", 11);
		else if (state == ST_SLEEPING)
			write(1, " is sleeping\n", 13);
	}
	pthread_mutex_unlock(&pars->print_mutex);
}

