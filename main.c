/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 16:08:03 by ssanei            #+#    #+#             */
/*   Updated: 2024/08/27 12:38:27 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	check_table_status(philos)
{
	
}

void	start_philo_threads(t_philos *philos)
{
	int	i;

	i = 0;
	while (i++ < philos->data->num_philos)
		handle_safe_thread(&(philos[i].thread_id), &philo_check_status,
			&philos[i], CREATE);
	check_table_status(philos);
}

int	main(int argc, char *argv[])
{
	t_data		data;
	t_philos	*philos;
	int			i;

	i = 0;
	if (check_input(argc, argv) == 0)
	{
		init_program_data(&data, argv);
		// if (!data.forks)
		// 	return (EXIT_FAILURE);
		philos = safe_malloc(sizeof(t_philos) * data.num_philos);
		init_philos(&data, philos);
		start_philo_threads(philos);
		while (i++ < philos->data->num_philos)
			handle_safe_thread(philos[i].thread_id, NULL, NULL, JOIN);
		// free(data.forks);
		return (0);
	}
	return (EXIT_FAILURE);
}
