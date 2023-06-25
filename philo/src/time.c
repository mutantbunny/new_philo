/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 03:36:45 by gmachado          #+#    #+#             */
/*   Updated: 2023/06/25 09:46:59 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	timestamp_in_ms(void)
{
	struct timeval	now_tv;

	gettimeofday(&now_tv, NULL);
	return ((now_tv.tv_sec) * 1000 + (now_tv.tv_usec) / 1000);
}

void	sleep_in_ms(long long sleep_time)
{
	long long	start_ts;

	start_ts = timestamp_in_ms();
	while (timestamp_in_ms() - start_ts < sleep_time)
		usleep(SLEEP_TIME_STEP);
}
