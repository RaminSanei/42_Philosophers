/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 16:08:03 by ssanei            #+#    #+#             */
/*   Updated: 2024/09/02 20:40:12 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	check_table_status(t_philos *philos, int i)
{
	// int	i;
	// i = 0;
	while (i < philos->data->num_philos)
	{
		pthread_mutex_lock(&(philos[i].data->print));
		if (get_precise_time()
			- philos[i].last_meal > philos[i].data->time_to_die)
		{
			philos[i].data->dead_philos++;
			if (philos[i].ate_count < philos[i].data->num_must_eat)
				printf("%ldms philo_ID %d %s\n", get_precise_time()
					- philos[i].data->start_time, philos[i].id, DIED);
			pthread_mutex_unlock(&(philos[i].data->print));
			break ;
		}
		pthread_mutex_unlock(&(philos[i].data->print));
		precise_sleep(1);
		i++;
	}
}

void	*check_death(void *philos)
{
	t_philos	*philo;
	int			i;

	philo = (t_philos *)philos;
	while (philo->data->dead_philos < philo->data->num_philos)
	{
		i = 0;
		while (i < philo->data->num_philos)
		// {
		// 	pthread_mutex_lock(&(philo[i].data->print));
		// 	if (get_precise_time()
		// 		- philo[i].last_meal > philo[i].data->time_to_die)
		// 	{
		// 		philo[i].data->dead_philos++;
		// 		if (philo[i].ate_count < philo[i].data->num_must_eat)
		// 			printf("%ldms philo_ID %d %s\n", get_precise_time()
		// 				- philo[i].data->start_time, philo[i].id, DIED);
		// 		pthread_mutex_unlock(&(philo[i].data->print));
		// 		break ;
		// 	}
		// 	pthread_mutex_unlock(&(philo[i].data->print));
		// 	precise_sleep(1);
		// 	i++;
	}
	return (NULL);
}

void	start_philo_threads(t_philos *philos, t_data *data)
{
	int			i;
	pthread_t	death_checker;

	// handle_safe_thread(&death_checker, check_death, philos, CREATE)
		// i = 0;
		// while (i < data->num_philos)
		// {
		// 	handle_safe_thread(&(philos[i].thread_id), &philo_check_status,
		// 		&philos[i], CREATE);
		// 	i++;
		// }
		// printf("num_philos: %d\n", data->num_philos);
		// while (data->dead_philos == 0)
		// {
		// 	check_table_status(philos, i);
		// }
		i = 0;
	while (i < data->num_philos)
	{
		handle_safe_thread(&(philos[i].thread_id), NULL, NULL, JOIN);
		i++;
	}
}

// void	philo_join_threads(t_philos *philos)
// {
// 	int	i;

// 	i = 0;
// 	while (i < philos->data->num_philos)
// 	{
// 		handle_safe_thread(&(philos[i].thread_id), NULL, NULL, JOIN);
// 		i++;
// 	}
// }

int	main(int argc, char *argv[])
{
	t_data		data;
	t_philos	*philos;

	if (!check_input(argc, argv))
	{
		init_program_data(&data, argv);
		philos = safe_malloc(sizeof(t_philos) * data.num_philos);
		init_philos(&data, philos);
		printf("hello\n");
		start_philo_threads(philos, &data);
		printf("world\n");
		// philo_join_threads(philos);
		free_allocated_memory(&data, philos);
		free(philos);
		free(data.forks);
		return (EXIT_SUCCESS);
	}
	else
		return (EXIT_FAILURE);
}
