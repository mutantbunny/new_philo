/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 22:10:33 by gmachado          #+#    #+#             */
/*   Updated: 2023/06/25 02:53:04 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isspace(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

int	ft_atoi(const char *nptr)
{
	int	is_negative;
	int	result;

	result = 0;
	is_negative = 0;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '-')
	{
		is_negative = 1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
	{
		result = 10 * result - (int)(*nptr - '0');
		nptr++;
	}
	if (is_negative)
		return (result);
	return (-result);
}

t_error	checked_atoi(const char *nptr, int *result)
{
	char *ptr;

	if (nptr == NULL)
		return (ERR_PARAMS);
	ptr = nptr;
	while (*ptr != '\0')
	{
		if ((*ptr < '0' || *ptr > '9') && *ptr != '+')
			return (ERR_PARAMS);
		++ptr;
	}
	*result = ft_atoi(*nptr);
	if (*result < 1)
		return (ERR_PARAMS);
	return (OK);
}
