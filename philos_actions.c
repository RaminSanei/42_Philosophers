/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 12:58:52 by ssanei            #+#    #+#             */
/*   Updated: 2024/09/02 19:14:42 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_status(t_philos *philo, char *status, char act)
{
	time_t	dt;

	pthread_mutex_lock(&(philo->data->print));
	dt = get_precise_time() - philo->data->start_time;
	if (act == 'e')
		philo->last_meal = get_precise_time();
	if (philo->data->dead_philos == 0)
		printf("%-8ldms philo %-3d %s\n", dt, philo->id, status);
	pthread_mutex_unlock(&(philo->data->print));
}

int	philo_eating(t_philos *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, TAKE_FORK, 't');
	if (philo->right_fork != NULL)
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, TAKE_FORK, 't');
		if (philo->alive == false)
		{
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
			return (EXIT_FAILURE);
		}
		print_status(philo, IS_EATING, 'e');
		philo->ate_count++;
		precise_sleep(philo->data->time_to_eat);
	}
	pthread_mutex_unlock(philo->left_fork);
	if (philo->left_fork != NULL)
		pthread_mutex_unlock(philo->right_fork);
	return (EXIT_SUCCESS);
}

bool	philo_is_dead(t_philos *philo)
{
	if (get_precise_time() - philo->last_meal > philo->data->time_to_die)
	{
		// print_status(philo, DIED, 'd');
		philo->alive = false;
		return (true);
	}
	return (false);
}

// void	sub_check_status(t_philos *p)
// {
// 	print_status(p, IS_SLEEPING, 's');
// 	precise_sleep(p->data->time_to_sleep);
// 	print_status(p, IS_THINKING, 't');
// }

// void	*philo_check_status(void *philo)
// {
// 	t_philos	*p;
// 	time_t		delay;

// 	p = (t_philos *)philo;
// 	delay = 12;
// 	if (p->id % 2 == 0)
// 		precise_sleep(p->data->time_to_eat / delay);
// 	while (philo_is_dead(p) == false && p->alive == true
// 		&& p->ate_count != p->data->num_must_eat)
// 	{

// 		printf("dead_philos: %d\n", p->data->dead_philos);
// 		// if(philo_is_dead(p))
// 		// 	break ;
// 		if (philo_eating(p) == EXIT_FAILURE)
// 			break ;
// 		if (p->ate_count == p->data->num_must_eat)
// 			break ;
// 		sub_check_status(p);
// 	}
// 	return (NULL);
// }

// void	*philo_check_status(void *philo)
// {
// 	t_philos	*p;
// 	time_t		delay;

// 	p = (t_philos *)philo;
// 	delay = 12;
// 	if (p->id % 2 == 0)
// 		precise_sleep(p->data->time_to_eat / delay);
// 	while (1)
// 	{
// 		// Debug: Checking philosopher's status
// 		// printf("Philo %d: Checking status...\n", p->id);
// 		// Check if philosopher is dead
// 		if (philo_is_dead(p) || !p->alive)
// 		{
// 			printf("Philo %d: Dead or no longer alive\n", p->id);
// 			break ;
// 		}
// 		// Check if philosopher has eaten enough
// 		// if (p->ate_count >= p->data->num_must_eat)
// 		// {
// 		// 	printf("cout: %d\n", p->ate_count);
// 		// 	printf("num_must_eat: %ld\n", p->data->num_must_eat);
// 		// 	printf("Philo %d: Finished eating required meals\n", p->id);
// 		// 	break ;
// 		// }
// 		// Philosopher tries to eat
// 		if (philo_eating(p) == EXIT_FAILURE)
// 		{
// 			printf("Philo %d: Failed to eat\n", p->id);
// 			break ;
// 		}
// 		// Perform sleep and thinking phases
// 		sub_check_status(p);
// 	}
// 	return (NULL);
// }

int	sub_check_status(t_philos *p)
{
	if (p->data->num_must_eat != -1 && p->ate_count == p->data->num_must_eat)
	{
		p->data->philos_full++;
		if (p->data->philos_full == p->data->num_philos)
		{
			p->data->dead_philos = 1;
			return (EXIT_FAILURE);
		}
	}
	print_status(p, IS_SLEEPING, 's');
	precise_sleep(p->data->time_to_sleep);
	print_status(p, IS_THINKING, 't');
	return (EXIT_SUCCESS);
}

void	*philo_check_status(void *philo)
{
	t_philos	*p;
	time_t		delay;

	p = (t_philos *)philo;
	delay = 12;
	if (p->id % 2 == 0)
		precise_sleep(p->data->time_to_eat / delay);
	while (p->data->dead_philos == 0)
	{
		if (philo_eating(p) == EXIT_FAILURE)
			return (NULL);
		if (p->right_fork != NULL)
		{
			if (sub_check_status(p) == EXIT_FAILURE)
				return (NULL);
		}
		else
			precise_sleep(p->data->time_to_die);
	}
}
