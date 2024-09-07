/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 16:08:03 by ssanei            #+#    #+#             */
/*   Updated: 2024/09/07 19:02:51 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	check_philosopher_death(t_d *obj, t_p *philo)
{
	pthread_mutex_lock(&(obj->monitoring));
	if ((get_precise_time() - philo->last_meal) > obj->time_to_die)
	{
		obj->dead_philos = 1;
		pthread_mutex_lock(&(obj->print));
		if (philo->ate_count < obj->num_must_eat)
		{
			printf("%-5ld %-5d died\n", (get_precise_time() - obj->start_time),
				philo->id);
		}
		pthread_mutex_unlock(&(obj->print));
	}
	pthread_mutex_unlock(&(obj->monitoring));
}

void	monitor_philosophers(t_d *obj, t_p *philo)
{
	int	i;

	while (obj->dead_philos == 0)
	{
		i = 0;
		while (i < obj->num_philos)
		{
			check_philosopher_death(obj, &philo[i]);
			if (obj->dead_philos)
				break ;
			i++;
		}
		precise_sleep(1);
	}
}

static int	sub_main_function(t_d *obj, t_p *philo)
{
	int	i;

	i = 0;
	while (i < obj->num_philos)
	{
		if (pthread_create(&(philo[i].thread_id), NULL, &philo_check_status,
				&philo[i]) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
		i++;
	}
	monitor_philosophers(obj, philo);
	i = 0;
	while (i < obj->num_philos)
	{
		if (pthread_join(philo[i].thread_id, NULL) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char *argv[])
{
	t_d	obj;
	t_p	*philo;
	int	sub;
	t_f	*fork;

	if (check_input(argc, argv) != EXIT_FAILURE)
	{
		init_program_data(&obj, argv);
		fork = init_forks(obj.num_philos);
		if (fork == NULL)
			return (EXIT_FAILURE);
		obj.forks = fork;
		philo = init_philos(&obj);
		if (philo == NULL)
			return (EXIT_FAILURE);
		sub = sub_main_function(&obj, philo);
		if (sub == EXIT_FAILURE)
			return (EXIT_FAILURE);
		destroy_mutex_function(&obj);
		free(obj.forks);
		free(philo);
		return (EXIT_SUCCESS);
	}
	else
		return (EXIT_FAILURE);
}
