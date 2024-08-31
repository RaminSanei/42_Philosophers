/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 12:58:52 by ssanei            #+#    #+#             */
/*   Updated: 2024/08/29 18:15:44 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	print_status(t_philos *philo, char *status)
{
	// handle_safe_mutex(&philo->data->print, LOCK);
	pthread_mutex_lock(&philo->data->print);
	printf("%ldms philo_ID %d %s\n", get_precise_time()
		- philo->data->start_time, philo->id, status);
	// handle_safe_mutex(&philo->data->print, UNLOCK);
	pthread_mutex_unlock(&philo->data->print);
	return (0);
}

int	philo_eating(t_philos *philo)
{
	// handle_safe_mutex((philo->right_fork), LOCK);
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, TAKE_FORK);
	if (philo->left_fork != NULL)
	{
		// handle_safe_mutex(philo->left_fork, LOCK);
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, TAKE_FORK);
		if (philo->alive == false)
		{
			// handle_safe_mutex(philo->left_fork, UNLOCK);
			pthread_mutex_unlock(philo->left_fork);
			// handle_safe_mutex(philo->right_fork, UNLOCK);
			pthread_mutex_unlock(philo->right_fork);
			return (EXIT_FAILURE);
		}
		print_status(philo, IS_EATING);
		philo->ate_count++;
		philo->last_meal = get_precise_time();
		precise_sleep(philo->data->time_to_eat);
	}
	// handle_safe_mutex(philo->right_fork, UNLOCK);
	pthread_mutex_unlock(philo->right_fork);
	if (philo->left_fork != NULL)
		// handle_safe_mutex(philo->left_fork, UNLOCK);
		pthread_mutex_unlock(philo->left_fork);
	return (EXIT_SUCCESS);
}

bool	philo_is_dead(t_philos *philo)
{
	if (get_precise_time() - philo->last_meal > philo->data->time_to_die)
	{
		print_status(philo, DIED);
		philo->alive = false;
		return (true);
	}
	return (false);
}

void	sub_check_status(t_philos *p)
{
	print_status(p, IS_SLEEPING);
	precise_sleep(p->data->time_to_sleep);
	print_status(p, IS_THINKING);
}

void	*philo_check_status(void *philo)
{
	t_philos	*p;
	time_t		delay;

	p = (t_philos *)philo;
	delay = 12;
	printf("delay: %ld\n", delay);
	if (p->id % 2 == 0)
		precise_sleep(p->data->time_to_eat / delay);
	while (philo_is_dead(p) == false && p->alive == true
		&& p->ate_count != p->data->num_must_eat)
	{
		if (philo_eating(p) == EXIT_FAILURE)
			break ;
		if (p->ate_count == p->data->num_must_eat)
			break ;
		sub_check_status(p);
	}
	return (NULL);
}
