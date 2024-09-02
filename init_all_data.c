/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 11:10:15 by ssanei            #+#    #+#             */
/*   Updated: 2024/09/02 19:11:30 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_program_data(t_data *data, char *argv[])
{
	t_mutex	*forks;
	int		i;

	i = 0;
	data->dead_philos = 0;
	data->num_philos = ft_atoi_long(argv[1]);
	forks = safe_malloc(sizeof(t_mutex) * data->num_philos);
	data->forks = forks;
	data->time_to_die = ft_atoi_long(argv[2]);
	data->time_to_eat = ft_atoi_long(argv[3]);
	data->time_to_sleep = ft_atoi_long(argv[4]);
	data->philos_full = 0;
	data->num_must_eat = -1;
	if (argv[5])
		data->num_must_eat = ft_atoi_long(argv[5]);
	pthread_mutex_init(&data->print, NULL);
	data->start_time = get_precise_time();
	while (i++ < data->num_philos)
		pthread_mutex_init(&data->forks[i], NULL);
}

void	sub_init_philos(t_data *data, t_philos *philos, int i)
{
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
	else if (data->num_philos == 1)
	{
		philos[i].left_fork = &(data->forks[0]);
		philos[i].right_fork = NULL;
	}
}

void	init_philos(t_data *data, t_philos *philos)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		philos[i].data = data;
		philos[i].id = i + 1;
		philos[i].last_meal = data->start_time;
		philos[i].alive = true;
		philos[i].ate_count = 0;
		philos[i].left_fork = &data->forks[i];
		sub_init_philos(data, philos, i);
		// handle_safe_thread(&(philos[i].thread_id), &philo_check_status,
		// 	&philos[i], CREATE);
		i++;
	}
	i = 0;
	while (i < data->num_philos)
	{
		handle_safe_thread(&(philos[i].thread_id), NULL, NULL, JOIN);
		i++;
	}
}
