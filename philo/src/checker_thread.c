/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_thread.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 05:04:13 by gmachado          #+#    #+#             */
/*   Updated: 2023/06/25 07:33:52 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_death(t_params *pars, int idx);

void	*check_death_handler(void *arg)
{
	t_params	*pars;
	int			idx;
	int			num_philos;
	long long	time_to_die;

	pars = arg;
	num_philos = pars->num_philos;
	time_to_die = pars->time_to_die;
	while (!get_dinner_over(pars))
	{
		idx = 0;
		while (idx < num_philos)
		{
			if (timestamp_in_ms() - get_last_meal_timestamp() > time_to_die)
			{
				end_dinner();
				print_death(pars, idx);
				return (NULL);
			}
			++idx;
		}
		usleep(100);
	}
	return (NULL);
}

static void	print_death(t_params *pars, int idx)
{
	pthread_mutex_lock(&pars->print_mutex);
	ft_putnbr(timestamp_in_ms() - pars->start_ts);
	write(1, " ", 1);
	ft_putnbr((long long)idx + 1);
	write(1, " died\n", 6);
	pthread_mutex_unlock(&pars->print_mutex);
}
