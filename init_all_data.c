/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 11:10:15 by ssanei            #+#    #+#             */
/*   Updated: 2024/08/16 11:31:30 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	init_philos(t_data *data, t_philos *philos)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		philos[i].id = i + 1;
		philos[i].data = data;
		philos[i].last_meal = data->start;
		i++;
	}
}
void	init_program_data(t_data *data, int argc, char *argv[])
{
	data->num_philos = ft_atoi_long(argv[1]);
	data->time_to_die = ft_atoi_long(argv[2]);
	data->time_to_eat = ft_atoi_long(argv[3]);
	data->time_to_sleep = ft_atoi_long(argv[4]);
	data->num_must_eat = 0;
	if (argc == 6)
		data->num_must_eat = ft_atoi_long(argv[5]);
	data->philos_full = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	pthread_mutex_init(&data->print, NULL);
	gettimeofday(&data->start, NULL);
}
