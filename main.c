/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 16:08:03 by ssanei            #+#    #+#             */
/*   Updated: 2024/08/19 19:49:29 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*philo_check_status(t_philos *philo)
{
	//
	return (NULL);
}

int	return_print_error(char *str)
{
	printf("%s\n", str);
	return (1);
}

int	start_philo_threads(t_philos *philos)
{
	int	i;

	i = 0;
	while (i++ < philos->data->num_philos)
	{
		if (pthread_create(&philos[i].thread, NULL, &philo_check_status,
				&philos[i]) != 0)
			return_print_error(ERROR_CREATE);
	}
	i = 0;
	while (i++ < philos->data->num_philos)
	{
		if (pthread_join(philos[i].thread, NULL) != 0)
			return_print_error(ERROR_JOIN);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data		data;
	t_philos	*philos;

	if (check_input(argc, argv) == 1)
		return (EXIT_FAILURE);
	init_program_data(&data, argv);
	if (!data.forks)
		return (EXIT_FAILURE);
	philos = malloc(sizeof(t_philos) * data.num_philos);
	if (!philos)
		return (EXIT_FAILURE);
	init_philos(&data, philos);
	start_philo_threads(philos);
	if (start_philo_threads(philos) == 1)
		return (EXIT_FAILURE);
	// free(data.forks);
	return (0);
}
