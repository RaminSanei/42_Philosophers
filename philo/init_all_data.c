/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 11:10:15 by ssanei            #+#    #+#             */
/*   Updated: 2024/09/07 17:16:05 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_f	*init_forks(int num_philos)
{
	t_f	*fork;
	int	i;

	fork = (t_f *)safe_malloc(sizeof(t_f) * num_philos);
	i = 0;
	while (i < num_philos)
	{
		pthread_mutex_init(&(fork[i].fork), NULL);
		i++;
	}
	return (fork);
}

void	init_program_data(t_d *data, char *argv[])
{
	data->num_philos = ft_atoi_long(argv[1]);
	data->time_to_die = ft_atoi_long(argv[2]);
	data->time_to_eat = ft_atoi_long(argv[3]);
	data->time_to_sleep = ft_atoi_long(argv[4]);
	data->dead_philos = 0;
	data->start_time = get_precise_time();
	pthread_mutex_init(&data->print, NULL);
	data->num_must_eat = INT_MAX;
	if (argv[5])
		data->num_must_eat = ft_atoi_long(argv[5]);
	pthread_mutex_init(&data->monitoring, NULL);
}

t_f	*take_fork(t_d *data, int i, int status)
{
	if (status == 0)
	{
		if (i + 1 == data->num_philos)
			return (&data->forks[0]);
		else
			return (&data->forks[i]);
	}
	else
	{
		if (i + 1 == data->num_philos)
		{
			if (data->num_philos == 1)
				return (NULL);
			else
				return (&data->forks[i]);
		}
		else
			return (&data->forks[i + 1]);
	}
	return (NULL);
}

t_p	*init_philos(t_d *data)
{
	t_p	*ph;
	int	i;

	ph = (t_p *)safe_malloc(sizeof(t_p) * data->num_philos);
	i = 0;
	while (i < data->num_philos)
	{
		ph[i].ate_count = 0;
		ph[i].status = 1;
		ph[i].id = i + 1;
		ph[i].last_meal = get_precise_time();
		ph[i].data = data;
		ph[i].fork_r = take_fork(data, i, 0);
		ph[i].fork_l = take_fork(data, i, 1);
		i++;
	}
	return (ph);
}
