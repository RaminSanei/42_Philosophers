/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 15:51:05 by ssanei            #+#    #+#             */
/*   Updated: 2024/08/27 16:14:50 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	error_exit(char *str)
{
	printf("%s\n", str);
	exit(EXIT_FAILURE);
}

time_t	get_precise_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1e3) + (time.tv_usec / 1e3));
}

void	precise_sleep(int time)
{
	long	start;

	start = get_precise_time();
	while (get_precise_time() - start < time)
		usleep(time);
}

void	free_allocated_memory(t_data *data, t_philos *philos)
{
	int	i;

	i = 0;
	while (i++ < data->num_philos)
	{
		handle_safe_mutex(philos[i].left_fork, DESTROY);
		handle_safe_mutex(philos[i].right_fork, DESTROY);
	}
	handle_safe_mutex(&data->print, DESTROY);
	free(philos);
	free(data->forks);
}
