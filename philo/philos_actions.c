/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 12:58:52 by ssanei            #+#    #+#             */
/*   Updated: 2024/09/07 19:20:26 by ssanei           ###   ########.fr       */
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
		printf("%-5ld %-5d %s", get_precise_time() - philo->data->start_time,
			philo->id, message);
	pthread_mutex_unlock(&philo->data->print);
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
