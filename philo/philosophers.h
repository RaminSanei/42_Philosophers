/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 16:08:03 by ssanei            #+#    #+#             */
/*   Updated: 2024/09/07 20:56:08 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define ERROR_MANY "Too many arguments.\n"
# define ERROR_FEW "Too few arguments.\n"
# define ERROR_INV_ARG "Invalid arguments detected.\n"
# define ERROR_JOIN "Error in joining thread.\n"
# define ERROR_CREATE "Error in creating thread.\n"
# define TAKE_FORK "has taken a fork\n"
# define EATING "is eating\n"
# define DIED "died\n"
# define SLEEPING "is sleeping\n"
# define THINKING "is thinking\n"
# define ERROR_MALLOC "Error: malloc failed\n"
# define NO_PHILO "Error:  no philosopher\n"
# define ERROR_NEG "Error: negative input is invalid\n"
# define ERROR_MANY_PHILO "Error: too many philosophers\n"
# define ERROR_LESS60 "Error: times should be more than 60\n"

typedef pthread_mutex_t	t_mutex;

typedef struct s_fork
{
	t_mutex				fork;
}						t_f;

typedef struct s_philos
{
	int					id;
	pthread_t			thread_id;
	struct s_fork		*fork_l;
	struct s_fork		*fork_r;
	struct s_data		*data;
	time_t				last_meal;
	int					ate_count;
	int					status;
}						t_p;

typedef struct s_data
{
	int					num_philos;
	time_t				time_to_die;
	time_t				time_to_eat;
	time_t				time_to_sleep;
	int					num_must_eat;
	struct s_fork		*forks;
	t_mutex				print;
	time_t				start_time;
	int					dead_philos;
	t_mutex				monitoring;

}						t_d;

int						check_input(int argc, char *argv[]);
long					ft_atoi_long(const char *str);
void					init_program_data(t_d *data, char *argv[]);
void					*philo_check_status(void *philo);
time_t					get_precise_time(void);
void					destroy_mutex_function(t_d *data);
void					precise_sleep(time_t time);
void					print_status(t_p *philo, int status, char *message);
t_f						*init_forks(int num);
t_p						*init_philos(t_d *data);
void					*safe_malloc(size_t size);
int						philos_eating(t_p *philo);

#endif