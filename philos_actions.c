/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 12:58:52 by ssanei            #+#    #+#             */
/*   Updated: 2024/08/27 12:55:46 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_precise_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1e3) + (time.tv_usec / 1e3));
}

void	precise_sleep(int time)
{
	long	start;

	start = get_precise_time();
	while (get_precise_time() - start < time)
		usleep(time);
}

int	print_status(t_philos *philo, char *status)
{
	handle_safe_mutex(&philo->data->print, LOCK);
	printf("%ld %d %s\n", get_precise_time() - philo->data->start_time,
		philo->id, status);
	handle_safe_mutex(&philo->data->print, UNLOCK);
	return (0);
}

int	philo_eating(t_philos *philo)
{
	handle_safe_mutex((philo->right_fork), LOCK);
	print_status(philo, TAKE_FORK);
	if (philo->left_fork != NULL)
	{
		handle_safe_mutex(philo->left_fork, LOCK);
		print_status(philo, TAKE_FORK);
		if (philo->alive == false)
		{
			handle_safe_mutex(philo->left_fork, UNLOCK);
			handle_safe_mutex(philo->right_fork, UNLOCK);
			return (EXIT_FAILURE);
		}
		print_status(philo, IS_EATING);
		philo->ate_count++;
		philo->last_meal = get_precise_time();
		precise_sleep(philo->data->time_to_eat);
	}
	handle_safe_mutex(philo->right_fork, UNLOCK);
	if (philo->left_fork != NULL)
		handle_safe_mutex(philo->left_fork, UNLOCK);
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

void	*philo_check_status(void *philo)
{
	t_philos	*p;

	p = (t_philos *)philo;
	if (p->id % 2 == 0)
		precise_sleep(p->data->time_to_eat / p->data->num_philos);
	while (p->alive == true && p->ate_count != p->data->num_must_eat)
	{
		if (philo_eating(p) == EXIT_FAILURE)
			return (NULL);
		if (p->ate_count == p->data->num_must_eat)
			return (NULL);
		print_status(p, IS_SLEEPING);
		precise_sleep(p->data->time_to_sleep);
		print_status(p, IS_THINKING);
	}
	return (NULL);
}
