/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 12:58:52 by ssanei            #+#    #+#             */
/*   Updated: 2024/09/05 09:15:09 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_is_dead(t_p *philo)
{
	if ((get_precise_time() - philo->last_meal) > philo->data->time_to_die)
	{
		philo->status = 0;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	print_status(t_p *philo, int status, char *message)
{
	pthread_mutex_lock(&philo->data->print);
	if (status == 1)
		philo->last_meal = get_precise_time();
	if (!philo->data->dead_philos)
		printf("%-8ld %-3d %s\n", get_precise_time()
			- philo->data->start_time, philo->id, message);
	pthread_mutex_unlock(&philo->data->print);
}

int	philos_eating(t_p *philo)
{
	pthread_mutex_lock(&philo->fork_r->fork);
	print_status(philo, 0, TAKE_FORK);
	if (philo->fork_l != NULL)
	{
		pthread_mutex_lock(&philo->fork_l->fork);
		print_status(philo, 0, TAKE_FORK);
		if (philo->data->dead_philos)
		{
			pthread_mutex_unlock(&philo->fork_r->fork);
			pthread_mutex_unlock(&philo->fork_l->fork);
			return (EXIT_FAILURE);
		}
		print_status(philo, 1, EATING);
		philo->ate_count++;
		precise_sleep(philo->data->time_to_eat);
	}
	pthread_mutex_unlock(&philo->fork_r->fork);
	if (philo->fork_l != NULL)
		pthread_mutex_unlock(&philo->fork_l->fork);
	return (EXIT_SUCCESS);
}

void	sub_philo_check(t_p *p)
{
	print_status(p, 0, SLEEPING);
	precise_sleep(p->data->time_to_sleep);
	print_status(p, 0, THINKING);
}

void	*philo_check_status(void *philo)
{
	t_p		*p;
	time_t	time;

	time = 10;
	p = (t_p *)philo;
	if (p->id % 2 == 0)
		precise_sleep(p->data->time_to_eat / time);
	while (!check_is_dead(p) && p->ate_count < p->data->num_must_eat
		&& p->status)
	{
		if (philos_eating(p) == EXIT_FAILURE)
			break ;
		if (p->ate_count == p->data->num_must_eat)
			break ;
		sub_philo_check(p);
	}
	return (NULL);
}
