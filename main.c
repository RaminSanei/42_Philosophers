/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 16:08:03 by ssanei            #+#    #+#             */
/*   Updated: 2024/08/29 18:11:58 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	check_table_status(t_philos *philos)
{
	int	i;

	i = 0;
	while (i < philos->data->num_philos)
	{
		// handle_safe_mutex(&(philos[i].data->print), LOCK);
		pthread_mutex_lock(&(philos[i].data->print));
		if (get_precise_time()
			- philos[i].last_meal > philos[i].data->time_to_die)
		{
			if (philos[i].ate_count < philos[i].data->num_must_eat)
				printf("%ldms philo_ID %d %s\n", get_precise_time()
					- philos[i].data->start_time, philos[i].id, DIED);
			philos[i].data->dead_philos++;
			// handle_safe_mutex(&(philos[i].data->print), UNLOCK);
			pthread_mutex_unlock(&(philos[i].data->print));
			break ;
		}
		// handle_safe_mutex(&(philos[i].data->print), UNLOCK);
		pthread_mutex_unlock(&(philos[i].data->print));
		precise_sleep(1);
		i++;
	}
}

void	start_philo_threads(t_philos *philos)
{
	int	i;

	while (philos->data->dead_philos == 0)
	{
		check_table_status(philos);
	}
	i = 0;
	while (i < philos->data->num_philos)
	{
		handle_safe_thread(&(philos[i].thread_id), NULL, NULL, JOIN);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_data		data;
	t_philos	*philos;

	if (!check_input(argc, argv))
	{
		init_program_data(&data, argv);
		philos = safe_malloc(sizeof(t_philos) * data.num_philos);
		init_philos(&data, philos);
		start_philo_threads(philos);
		free_allocated_memory(&data, philos);
		free(philos);
		free(data.forks);
		return (0);
	}
	else
		return (EXIT_FAILURE);
}
