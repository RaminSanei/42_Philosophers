/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 11:10:15 by ssanei            #+#    #+#             */
/*   Updated: 2024/08/20 18:26:29 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_program_data(t_data *data, char *argv[])
{
	pthread_mutex_t	*forks;

	data->num_philos = ft_atoi_long(argv[1]);
	data->time_to_die = ft_atoi_long(argv[2]);
	data->time_to_eat = ft_atoi_long(argv[3]);
	data->time_to_sleep = ft_atoi_long(argv[4]);
	data->dead_philos = 0;
	forks = safe_malloc(sizeof(pthread_mutex_t) * data->num_philos);
	data->num_must_eat = INT_MAX;
	if (argv[5])
		data->num_must_eat = ft_atoi_long(argv[5]);
	data->philos_full = 0;
	data->forks = forks;
	pthread_mutex_init(&data->print, NULL);
	gettimeofday(&data->start_time, NULL);
}

void	init_philos(t_data *data, t_philos *philos)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		philos[i].id = i;
		philos[i].data = data;
		philos[i].last_meal = data->start_time;
		philos[i].status = THINKING;
		if (data->num_philos > 1)
		{
			if (i == data->num_philos - 1)
			{
				philos[i].left_fork = &(data->forks[0]);
				philos[i].right_fork = &(data->forks[i]);
			}
			else
			{
				philos[i].left_fork = &(data->forks[i]);
				philos[i].right_fork = &(data->forks[i + 1]);
			}
		}
		else
		{
			philos[i].left_fork = &(data->forks[0]);
			philos[i].right_fork = NULL;
		}
		i++;
	}
	i = 0;
	while (i < data->num_philos)
	{
		pthread_create(&philos[i].thread_id, NULL, philo_check_status,
			&philos[i]);
		i++;
	}
}
