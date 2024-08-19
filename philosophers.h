/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 16:08:03 by ssanei            #+#    #+#             */
/*   Updated: 2024/08/19 19:49:18 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define ERROR_MANY "Too many arguments.\n"
# define ERROR_FEW "Too few arguments.\n"
# define ERROR_INV_ARG "Invalid arguments.\n"
# define ERROR_JOIN "Error in joining thread.\n"
# define ERROR_CREATE "Error in creating thread.\n"

typedef struct s_philos
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_data	*data;
	time_t			last_meal;
}					t_philos;

typedef struct s_data
{
	int				num_philos;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	int				num_must_eat;
	int				philos_full;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	time_t			start_time;
}					t_data;

long int			check_input(int argc, char *argv[]);
void				init_program_data(t_data *data, char *argv[]);
int					return_error(char *str);
void				init_philos(t_data *data, t_philos *philos);

#endif