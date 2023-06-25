/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 04:30:44 by gmachado          #+#    #+#             */
/*   Updated: 2023/06/25 09:14:17 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_fork	*first_fork(t_philo *philo)
{
	int philo_number;

	philo_number = philo->number;
	if (philo_number % 2 == 0)
		return (philo->pars->forks + philo_number);
	return (philo->pars->forks + ((philo_number + 1) % philo->pars->num_philos));
}

t_fork	*second_fork(t_philo *philo)
{
	int philo_number;

	if (philo->pars->num_philos == 1)
		return (NULL);
	philo_number = philo->number;
	if (philo_number % 2 == 0)
		return (philo->pars->forks + ((philo_number + 1) % philo->pars->num_philos));
	return (philo->pars->forks + philo_number);
}

void	print_state(t_params *pars, int idx, t_state state)
{
	pthread_mutex_lock(&pars->print_mtx);
	if (get_dinner_over(pars) == FALSE)
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
	pthread_mutex_unlock(&pars->print_mtx);
}

void	ft_putnbr(long long nbr)
{
	char	digit;

	if (nbr < 0)
		return ;
	if (nbr < 10)
	{
		digit = (unsigned char)nbr + '0';
		write(1, &digit, 1);
		return ;
	}
	ft_putnbr(nbr / 10);
	ft_putnbr(nbr % 10);
}
