/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 12:58:52 by ssanei            #+#    #+#             */
/*   Updated: 2024/08/20 16:20:54 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	print_status(t_philos *philo, char *status)
{
	pthread_mutex_lock(&philo->data->print);
	printf("%ld %d %s\n", get_time() - philo->data->start_time, philo->id + 1,
		status);
	pthread_mutex_unlock(&philo->data->print);
	return (0);
}

void	philo_eating(t_philos *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, TAKE_FORK);
	if (philo->right_fork != NULL)
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, TAKE_FORK);
		print_status(philo, IS_EATING);
	philo->last_meal = get_time();
	philo->status = EATING;
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(philo->right_fork);
	}
	else
		print_status(philo, TAKE_FORK);
	pthread_mutex_unlock(philo->left_fork);
	// return (0);
}

void	*philo_check_status(void *philo)
{
	t_philos	*p;

	p = (t_philos *)philo;
	if (p->id % 2 == 0)
		usleep(130);
	while (p->data->dead_philos == 0)
	{
		philo_eating(p);
		// if (philo_eating(p) == 0)
			// return (NULL);
		if(p->ate_count == p->data->num_must_eat)
		{
			// p->data->philos_full++;
			return (NULL);
		}
		
	}
	return (NULL);
}
