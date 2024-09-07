/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_eating.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 19:18:57 by ssanei            #+#    #+#             */
/*   Updated: 2024/09/07 19:20:09 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	try_acquire_forks(t_p *philo)
{
	pthread_mutex_lock(&philo->fork_r->fork);
	print_status(philo, 0, TAKE_FORK);
	if (philo->fork_l != NULL)
	{
		pthread_mutex_lock(&philo->fork_l->fork);
		print_status(philo, 0, TAKE_FORK);
		return (EXIT_FAILURE);
	}
	pthread_mutex_unlock(&philo->fork_r->fork);
	return (EXIT_SUCCESS);
}

void	release_forks(t_p *philo)
{
	pthread_mutex_unlock(&philo->fork_r->fork);
	if (philo->fork_l != NULL)
		pthread_mutex_unlock(&philo->fork_l->fork);
}

int	check_philosopher_status(t_p *philo)
{
	pthread_mutex_lock(&(philo->data->monitoring));
	if (philo->data->dead_philos)
	{
		pthread_mutex_unlock(&(philo->data->monitoring));
		return (EXIT_FAILURE);
	}
	pthread_mutex_unlock(&(philo->data->monitoring));
	return (EXIT_SUCCESS);
}

void	eat(t_p *philo)
{
	pthread_mutex_lock(&(philo->data->monitoring));
	print_status(philo, 1, EATING);
	philo->ate_count++;
	pthread_mutex_unlock(&(philo->data->monitoring));
	precise_sleep(philo->data->time_to_eat);
}

int	philos_eating(t_p *philo)
{
	if (!try_acquire_forks(philo))
		return (EXIT_FAILURE);
	if (check_philosopher_status(philo))
	{
		release_forks(philo);
		return (EXIT_FAILURE);
	}
	eat(philo);
	release_forks(philo);
	return (EXIT_SUCCESS);
}
