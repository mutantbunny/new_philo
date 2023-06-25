/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 03:36:45 by gmachado          #+#    #+#             */
/*   Updated: 2023/06/25 03:39:57 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	timestamp_in_ms(void)
{
	struct timeval	now_tv;

	gettimeofday(&now_tv, NULL);
	return ((now_tv.tv_sec) * 1000 + (now_tv.tv_usec) / 1000);
}
