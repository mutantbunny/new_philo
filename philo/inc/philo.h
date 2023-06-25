/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 21:50:38 by gmachado          #+#    #+#             */
/*   Updated: 2023/06/25 06:35:28 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <sys/select.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <bits/pthreadtypes.h>

# define CHECK_EATING_TIME 500

typedef pthread_mutex_t	t_fork;
typedef struct s_params	t_params;
typedef struct s_philo	t_philo;

typedef enum e_error
{
	OK,
	ERR_PARAMS,
	ERR_ALLOC,
	ERR_MUTEX,
	ERR_THREAD
}	t_error;

typedef enum e_state
{
	ST_THINKING,
	ST_GOT_FORK,
	ST_EATING,
	ST_SLEEPING,
	ST_DEAD
}	t_state;

typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

struct s_params
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_meals;
	int				num_must_eat;
	t_bool			dinner_over;
	long long		start_ts;
	t_fork			*forks;
	t_philo			*philos;
	pthread_t		monitor_thread;
	pthread_mutex_t	print_mtx;
	pthread_mutex_t	dinner_over_mtx;
	pthread_mutex_t	must_eat_mtx;
};

struct s_philo
{
	int				number;
	int				remaining_meals;
	long long		last_meal_ts;
	t_fork			*first_fork;
	t_fork			*second_fork;
	t_params		*pars;
	pthread_mutex_t	last_meal_mtx;
	pthread_t		thread;
};

#endif
