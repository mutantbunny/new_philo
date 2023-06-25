/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 05:11:51 by gmachado          #+#    #+#             */
/*   Updated: 2023/06/25 06:49:04 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	get_dinner_over(t_params *pars)
{
	t_bool	result;

	pthread_mutex_lock(pars->dinner_over_mtx);
	result = pars->dinner_over;
	pthread_mutex_unlock(pars->dinner_over_mtx);
	return (result);
}
