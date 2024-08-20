/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 16:08:03 by ssanei            #+#    #+#             */
/*   Updated: 2024/08/20 18:27:39 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	return_print_error(char *str)
{
	printf("%s\n", str);
	return (1);
}

int	start_philo_threads(t_philos *philos)
{
	int			i;
	pthread_t	check_death;

	i = 0;
	while (i++ < philos->data->num_philos)
	{
		if (pthread_create(&philos[i].thread_id, NULL, &philo_check_status,
				&philos[i]) != 0)
			return_print_error(ERROR_CREATE);
	}
	//
	// i = 0;
	// while (i++ < philos->data->num_philos)
	// {
	// 	if (pthread_join(philos[i].thread, NULL) != 0)
	// 		return_print_error(ERROR_JOIN);
	// }
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data		data;
	t_philos	*philos;
	int			i;

	i = 0;
	if (check_input(argc, argv) == 1)
		return (EXIT_FAILURE);
	init_program_data(&data, argv);
	if (!data.forks)
		return (EXIT_FAILURE);
	philos = safe_malloc(sizeof(t_philos) * data.num_philos);
	init_philos(&data, philos);
	start_philo_threads(philos);
	if (start_philo_threads(philos) == 1)
		return (EXIT_FAILURE);
	while (i++ < philos->data->num_philos)
	{
		if (pthread_join(philos[i].thread_id, NULL) != 0)
			return_print_error(ERROR_JOIN);
	}
	// free(data.forks);
	return (0);
}
